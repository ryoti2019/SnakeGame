#include <string>
#include <DxLib.h>
#include "CharImage.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#define CHAR_SIZE_X 32
#define CHAR_SIZE_Y 32
CharImage::CharImage()
{
}

CharImage::~CharImage()
{
}

bool CharImage::Init(CharID charID)
{
    if (charID >= CharID::DRAW || charID < CharID::BOY)
    {
        return false;
    }

    std::string charNameList[static_cast<int>(CharID::MAX)] = 
    {
        "BOY",
        "GIRL",
        "UNCLE",
        "CAT",
        "WAR",
        ""
    };

    std::string fileName = "./Resource/image/" + charNameList[static_cast<int>(charID)] + ".png";

    if (LoadDivGraph(
        fileName.c_str(),
        ANIME_IMAGE_MAX * static_cast<int>(Dir::Max),
        ANIME_IMAGE_MAX,
        static_cast<int>(Dir::Max),
        CHAR_SIZE_X,
        CHAR_SIZE_Y,
        &chipImage_[0][0]
    ) == -1)
    {
        TRACE("キャラ画像ファイルの読み込み失敗\n");
        return false;
    }

    charID_ = charID;

    return false;
}

bool CharImage::Release(void)
{
    for (int dir = 0; dir < static_cast<int>(Dir::Max); dir++)
    {
        for (int anime = 0; anime < ANIME_IMAGE_MAX; anime++)
        {
            DeleteGraph(chipImage_[dir][anime]);
        }
    }

 
    return true;
}

CharID CharImage::GetID(void) const
{
    return charID_;
}
