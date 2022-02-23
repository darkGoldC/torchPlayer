#ifndef ITPEs_out_H
#define ITPEs_out_H
#include <iostream>

#define AUDIO_REPLAY_GAIN_MAX (2)
#define AUDIO_REPLAY_GAIN_TRACK (0)
#define AUDIO_REPLAY_GAIN_ALBUM (1)

typedef enum _audio_channel_type_t
{
    AUDIO_CHANNEL_TYPE_BITMAP,//位图模式
    AUDIO_CHANNEL_TYPE_AMBISONICS,//立体环绕模式
} audio_channel_type_t;

typedef struct _audio_format_t
{
    int nFormat;//音频格式
    unsigned int    nSampleRate;//音频采样率
    int             nPhysicalChannels;//音频通道数

    int             nChanMode;//自定义通道模式
    //通道类型
    audio_channel_type_t    nChannelType;
    unsigned int            nBytesPerFrame;//一个压缩帧多少字节
    unsigned int            nFrameLength;//一个压缩帧中包含的样本帧数

    unsigned                nBitspersample;//采样位数
    unsigned                nBlockalign;//每个音频编码帧所需字节数
    unsigned                nChannels;//音频通道数
}audio_format_t;

typedef struct _audio_replay_gain_t
{
    /* true if we have the peak value */
    bool pb_peak[AUDIO_REPLAY_GAIN_MAX];
    /* peak value where 1.0 means full sample value */
    float      pf_peak[AUDIO_REPLAY_GAIN_MAX];

    /* true if we have the gain value */
    bool pb_gain[AUDIO_REPLAY_GAIN_MAX];
    /* gain value in dB */
    float      pf_gain[AUDIO_REPLAY_GAIN_MAX];
}audio_replay_gain_t;

#define VIDEO_PALETTE_COLORS_MAX 256

struct video_palette_t
{
    int i_entries;      /**< to keep the compatibility with libavcodec's palette */
    uint8_t palette[VIDEO_PALETTE_COLORS_MAX][4];  /**< 4-byte RGBA/YUVA palette */
};

//视频方向
typedef enum video_orientation_t
{
    ORIENT_TOP_LEFT = 0, //
    ORIENT_TOP_RIGHT, //横向翻转
    ORIENT_BOTTOM_LEFT, //竖直翻转
    ORIENT_BOTTOM_RIGHT,
    ORIENT_LEFT_TOP,
    ORIENT_LEFT_BOTTOM,
    ORIENT_RIGHT_TOP,
    ORIENT_RIGHT_BOTTOM,

    ORIENT_NORMAL      = ORIENT_TOP_LEFT,
    ORIENT_TRANSPOSED  = ORIENT_LEFT_TOP,
    ORIENT_ANTI_TRANSPOSED = ORIENT_RIGHT_BOTTOM,
    ORIENT_HFLIPPED    = ORIENT_TOP_RIGHT,
    ORIENT_VFLIPPED    = ORIENT_BOTTOM_LEFT,
    ORIENT_ROTATED_180 = ORIENT_BOTTOM_RIGHT,
    ORIENT_ROTATED_270 = ORIENT_LEFT_BOTTOM,
    ORIENT_ROTATED_90  = ORIENT_RIGHT_TOP,
} video_orientation_t;

//色域
typedef enum video_color_primaries_t
{
    COLOR_PRIMARIES_UNDEF,
    COLOR_PRIMARIES_BT601_525,
    COLOR_PRIMARIES_BT601_625,
    COLOR_PRIMARIES_BT709,
    COLOR_PRIMARIES_BT2020,
    COLOR_PRIMARIES_DCI_P3,
    COLOR_PRIMARIES_FCC1953,
#define COLOR_PRIMARIES_SRGB            COLOR_PRIMARIES_BT709
#define COLOR_PRIMARIES_SMTPE_170       COLOR_PRIMARIES_BT601_525
#define COLOR_PRIMARIES_SMTPE_240       COLOR_PRIMARIES_BT601_525 /* Only differs from 1e10-4 in white Y */
#define COLOR_PRIMARIES_SMTPE_RP145     COLOR_PRIMARIES_BT601_525
#define COLOR_PRIMARIES_EBU_3213        COLOR_PRIMARIES_BT601_625
#define COLOR_PRIMARIES_BT470_BG        COLOR_PRIMARIES_BT601_625
#define COLOR_PRIMARIES_BT470_M         COLOR_PRIMARIES_FCC1953
#define COLOR_PRIMARIES_MAX             COLOR_PRIMARIES_FCC1953
} video_color_primaries_t;

//色彩空间
typedef enum video_color_space_t
{
    COLOR_SPACE_UNDEF,
    COLOR_SPACE_BT601,
    COLOR_SPACE_BT709,
    COLOR_SPACE_BT2020,
#define COLOR_SPACE_SRGB      COLOR_SPACE_BT709
#define COLOR_SPACE_SMPTE_170 COLOR_SPACE_BT601
#define COLOR_SPACE_SMPTE_240 COLOR_SPACE_SMPTE_170
#define COLOR_SPACE_MAX       COLOR_SPACE_BT2020
} video_color_space_t;

typedef enum video_transfer_func_t
{
    TRANSFER_FUNC_UNDEF,
    TRANSFER_FUNC_LINEAR,
    TRANSFER_FUNC_SRGB /*< Gamma 2.2 */,
    TRANSFER_FUNC_BT470_BG,
    TRANSFER_FUNC_BT470_M,
    TRANSFER_FUNC_BT709,
    TRANSFER_FUNC_SMPTE_ST2084,
    TRANSFER_FUNC_SMPTE_240,
    TRANSFER_FUNC_HLG,
#define TRANSFER_FUNC_BT2020            TRANSFER_FUNC_BT709
#define TRANSFER_FUNC_SMPTE_170         TRANSFER_FUNC_BT709
#define TRANSFER_FUNC_SMPTE_274         TRANSFER_FUNC_BT709
#define TRANSFER_FUNC_SMPTE_293         TRANSFER_FUNC_BT709
#define TRANSFER_FUNC_SMPTE_296         TRANSFER_FUNC_BT709
#define TRANSFER_FUNC_ARIB_B67          TRANSFER_FUNC_HLG
#define TRANSFER_FUNC_MAX               TRANSFER_FUNC_HLG
} video_transfer_func_t;

//视频色彩位置
typedef enum video_chroma_location_t
{
    CHROMA_LOCATION_UNDEF,
    CHROMA_LOCATION_LEFT,   /*< Most common in MPEG-2 Video, H.264/265 */
    CHROMA_LOCATION_CENTER, /*< Most common in MPEG-1 Video, JPEG */
    CHROMA_LOCATION_TOP_LEFT,
    CHROMA_LOCATION_TOP_CENTER,
    CHROMA_LOCATION_BOTTOM_LEFT,
    CHROMA_LOCATION_BOTTOM_CENTER,
#define CHROMA_LOCATION_MAX CHROMA_LOCATION_BOTTOM_CENTER
} video_chroma_location_t;

//视点模式
typedef enum video_multiview_mode_t
{
    /* No stereoscopy: 2D picture. */
    MULTIVIEW_2D = 0,

    /* Side-by-side with left eye first. */
    MULTIVIEW_STEREO_SBS,

    /* Top-bottom with left eye first. */
    MULTIVIEW_STEREO_TB,

    /* Row sequential with left eye first. */
    MULTIVIEW_STEREO_ROW,

    /* Column sequential with left eye first. */
    MULTIVIEW_STEREO_COL,

    /* Frame sequential with left eye first. */
    MULTIVIEW_STEREO_FRAME,

    /* Checkerboard pattern with left eye first. */
    MULTIVIEW_STEREO_CHECKERBOARD,
} video_multiview_mode_t;

//投影模式
typedef enum video_projection_mode_t
{
    PROJECTION_MODE_RECTANGULAR = 0,
    PROJECTION_MODE_EQUIRECTANGULAR,

    PROJECTION_MODE_CUBEMAP_LAYOUT_STANDARD = 0x100,
} video_projection_mode_t;

typedef struct _video_format_t
{
    int             nChroma;//视频色度
    unsigned int    nWidth;//视频宽度
    unsigned int    nHeight;//视频高度
    unsigned int    nXOffset;//视频开始x位置
    unsigned int    nYOffset;//视频开始y位置
    unsigned int    nVisibleWidth;//视频可视宽度
    unsigned int    nVisibleHeight;//视频可视高度

    unsigned int    nBitsPerPixel;//每个像素多少位
    unsigned int    nSarNum;//宽度比
    unsigned int    nSarDen;//宽度比分母

    unsigned int    nFrameRateNum;//帧率分子
    unsigned int    nFrameRateBase;//帧率分母

    unsigned int    nRMask, nGMask, nBMask;//颜色分量值
    int             nRRshift, nLRshift;
    int             nRGshift, nLGshift;
    int             nRBshift, nLBshift;

    video_palette_t         pPalette;
    video_orientation_t     nOrientation;//视频方向
    video_color_primaries_t nPrimaries;//色域空间
    video_transfer_func_t   nTransfer;//色彩转换
    video_color_space_t     nSpace;//色彩空间YCbCr color space
    bool                    bColorRangeFull;//0-255 instead of 16-235

    video_chroma_location_t nChroma_location;//YCbCr
    video_multiview_mode_t  nMultiview_mode;//视点模式, 2d,3d
    video_projection_mode_t nProjectionMode;//投影模式
    //viewpoint_t pose;
    struct{
        unsigned short  nPrimaries[3*2];
        unsigned short  nWhite_poiont[2];
        unsigned int    nMax_luminance;
        unsigned int    nMin_luminance;
    } mastering;
    struct {
        /* similar to CTA-861.3 content light level */
        uint16_t MaxCLL;  /* max content light level */
        uint16_t MaxFALL; /* max frame average light level */
    } lighting;
    unsigned int    nCubemapPadding;//立体填料
}video_format_t;

enum es_format_category_e
{
    UNKNOWN_ES = 0x00,
    VIDEO_ES,
    AUDIO_ES,
    SPU_ES,
    DATA_ES,
};

typedef  struct  _es_format_t
{
    void    init(const es_format_category_e nInCat, int nCodec)
    {
        nCat = (es_format_category_e)nCat;
        nCodeType = nCodec;

        if(nCat == VIDEO_ES)
        {
            this->videoFormat.nChroma = 0;
            //视角初始化
            //fmt.videoFormat.pose
        }
        bPacketized = true;
    }
    es_format_category_e    nCat = UNKNOWN_ES;//es 类型
    int                     nCodeType = 0;//字幕解码器索引
    int                     nOriginalCodeType = 0;//原始编码类型
    int                     nId = -1;//es id
    int                     nGroupId = -1;//group id
    int                     nPriority = 0;//属性
    std::string             strLanguageName;//语言名称
    union
    {
        struct {
            audio_format_t      audioFormat;//音频格式
            audio_replay_gain_t audioReplayGain;//音频重播增益
        };
        video_format_t videoFormat;
        //subs_format_t subs;//字幕格式
    };

    unsigned int    nBitrate = -1;//es流的比特率
    int             nProfile = -1;
    int             nLevel = -1;

    bool            bPacketized = false;//数据是否是打包的
    std::string     strExtra;//额外数据,部分解码器或封装器使用
}es_format_t;

#endif
