//
// Created by Max Heartfield on 11.03.18.
//

#include "DicomUtils.h"

QImage DicomUtils::fromDicomFile(const QString &fileName) {
    unique_ptr<DataSet> ds(CodecFactory::load(fileName.toStdString()));
    unique_ptr<Image> image(ds->getImageApplyModalityTransform(0));
    unique_ptr<ReadingDataHandlerNumeric> dataHandler(image->getReadingDataHandler());
    TransformsChain chain;

    if (ColorTransformsFactory::isMonochrome(image->getColorSpace())) {
        VOILUT voilutTransform;
        std::uint32_t width = image->getWidth();
        std::uint32_t height = image->getHeight();
        vois_t vois = ds->getVOIs();
        vector<shared_ptr<LUT>> luts;
        for (size_t scanLUTs(0);; ++scanLUTs) {
            try {
                auto lut = shared_ptr<LUT>(ds->getLUT(TagId(tagId_t::VOILUTSequence_0028_3010), scanLUTs));
                luts.push_back(move(lut));
            }
            catch (const MissingDataElementError &) {
                break;
            }
        }

        if (!vois.empty()) {
            voilutTransform.setCenterWidth(vois[0].center, vois[0].width);
        } else if (!luts.empty()) {
            voilutTransform.setLUT(*(luts.front().get()));
        } else {
            voilutTransform.applyOptimalVOI(*image, 0, 0, width, height);
        }

        chain.addTransform((voilutTransform));
    }
    DrawBitmap bitmap(chain);
    auto size = bitmap.getBitmap(*image, drawBitmapType_t::drawBitmapRGBA, 2, nullptr, 0);
    std::string buffer(size, char(0));
    bitmap.getBitmap(*image, imebra::drawBitmapType_t::drawBitmapRGBA, 2, &(buffer.at(0)), size);
    return QImage(reinterpret_cast<const unsigned char *>(buffer.c_str()), image->getWidth(), image->getHeight(),
                  QImage::Format_RGBA8888);
}

vector<tuple<QString, QString>> DicomUtils::getTags(const QString &fileName) {
    unique_ptr<DataSet> ds(CodecFactory::load(fileName.toStdString()));
    vector<tuple<QString, QString>> vec;
    for (auto &tagId : ds->getTags()) {
        try {
            tuple<QString, QString> keyValuePair(SS2QS(DicomDictionary::getTagName(tagId)),
                                                 SS2QS(ds->getString(tagId, 0, "")));
            vec.push_back(keyValuePair);
        }
        catch (DictionaryUnknownTagError &) {
            continue;
        }
    }
    return vec;
};