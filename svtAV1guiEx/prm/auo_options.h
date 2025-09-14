// -----------------------------------------------------------------------------------------
// x264guiEx/x265guiEx/svtAV1guiEx/ffmpegOut/QSVEnc/NVEnc/VCEEnc by rigaya
// -----------------------------------------------------------------------------------------
// The MIT License
//
// Copyright (c) 2010-2022 rigaya
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// --------------------------------------------------------------------------------------------

#ifndef _AUO_OPTIONS_H_
#define _AUO_OPTIONS_H_

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <string>
#include <limits>

#include "auo.h"
#include "auo_settings.h"

//エンコードモード
enum {
    ENC_RC_QP = 0,
    ENC_RC_BITRATE,
};

//QPの最大値
const int ENC_QP_MAX_8BIT  = 69;
const int ENC_QP_MAX_10BIT = 81;

//差がこのくらいなら等しいとみなす(オプション用なのでこのくらいで十分)
const float EPS_FLOAT = 1.0e-4f;

#if ENCODER_X265
static const int AUO_KEYINT_MAX_AUTO = 0;
#elif ENCODER_X264 || ENCODER_SVTAV1
static const int AUO_KEYINT_MAX_AUTO = -1;
#endif

//マクロブロックタイプの一般的なオプション
enum {
    MB_PARTITION_NONE = 0x00000000,
    MB_PARTITION_P8x8 = 0x00000001,
    MB_PARTITION_B8x8 = 0x00000002,
    MB_PARTITION_P4x4 = 0x00000004,
    MB_PARTITION_I8x8 = 0x00000008,
    MB_PARTITION_I4x4 = 0x00000010,
    MB_PARTITION_ALL  = 0x0000001F,
};

enum {
    OUT_CSP_YUV400,
    OUT_CSP_YV12,
    OUT_CSP_YUV422,
    OUT_CSP_YUV444,
    OUT_CSP_RGB,
    OUT_CSP_YUY2,
    OUT_CSP_NV12,
    OUT_CSP_NV16,
    OUT_CSP_P010,
    OUT_CSP_YUV444_16,
    OUT_CSP_RGBA,
    OUT_CSP_RGBA_16,
};

enum {
    YC48_COLMAT_CONV_AUTO,
    YC48_COLMAT_CONV_NONE,
    YC48_COLMAT_CONV_BT709,
};

enum {
    AUTO_NPASS_NONE = 0,
    AUTO_NPASS_AMP,
    AUTO_NPASS_CRF,
};

//x264のinput-cspとして使用するもの
//OUT_CSP_NV12, OUT_CSP_YUV444, OUT_CSP_RGB に合わせる
static const TCHAR * const specify_csp[] = {
    _T("yuv400"), //OUT_CSP_YUV400
    _T("yuv420"), //OUT_CSP_YV12
    _T("yuv422"), //OUT_CSP_YUV422
    _T( "yuv444"), //OUT_CSP_YUV444
    _T("rgb")   //OUT_CSP_RGB
};
//文字列を引数にとるオプションの引数リスト
//OUT_CSP_NV12, OUT_CSP_YUV444, OUT_CSP_RGB に合わせる
const ENC_OPTION_STR list_output_csp[] = {
    { _T("yuv400"), AUO_MES_UNKNOWN, L"yuv400" },
    { _T("yuv420"), AUO_MES_UNKNOWN, L"yuv420" },
    { _T("yuv422"), AUO_MES_UNKNOWN, L"yuv422" },
    { _T("yuv444"), AUO_MES_UNKNOWN, L"yuv444" },
    { _T("rgb"),    AUO_MES_UNKNOWN, L"rgb"    },
    { nullptr,    AUO_MES_UNKNOWN, 0      }
};

typedef struct CX_DESC_AUO {
    const wchar_t *desc;
    AuoMes mes;
    int value;
} CX_DESC_AUO;

enum {
    COLOR_MATRIX_AUTO = 0,
};
const int COLOR_MATRIX_THRESHOLD = 720;

const CX_DESC_AUO list_color_range[] = {
    { L"auto",  AUO_MES_UNKNOWN, 0 },
    { L"pc",    AUO_MES_UNKNOWN, 1 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_colorprim[] = {
    { L"undef",     AUO_OPTION_VUI_UNDEF, 2   },
    { L"auto",      AUO_OPTION_VUI_AUTO, COLOR_MATRIX_AUTO   },
    { L"bt709",     AUO_MES_UNKNOWN, 1   },
    //{ L"smpte170m", AUO_MES_UNKNOWN, 3 },
    { L"bt470m",   AUO_MES_UNKNOWN, 4   },
    { L"bt470bg",  AUO_MES_UNKNOWN, 5   },
    { L"bt601",    AUO_MES_UNKNOWN, 6   },
    { L"smpte240", AUO_MES_UNKNOWN, 7   },
    { L"film",     AUO_MES_UNKNOWN, 8   },
    { L"bt2020",   AUO_MES_UNKNOWN, 9   },
    { L"xyz",      AUO_MES_UNKNOWN, 10  },
    { L"smpte431", AUO_MES_UNKNOWN, 11  },
    { L"smpte432", AUO_MES_UNKNOWN, 12  },
    { L"ebu3213",  AUO_MES_UNKNOWN, 22  },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_transfer[] = {
    { L"undef",         AUO_OPTION_VUI_UNDEF, 2  },
    { L"auto",          AUO_OPTION_VUI_AUTO, COLOR_MATRIX_AUTO  },
    { L"bt709",         AUO_MES_UNKNOWN, 1  },
    //{ L"smpte170m",     AUO_MES_UNKNOWN, 3    },
    { L"bt470m",        AUO_MES_UNKNOWN,  4 },
    { L"bt470bg",       AUO_MES_UNKNOWN,  5 },
    { L"bt601",         AUO_MES_UNKNOWN,  6 },
    { L"smpte240",      AUO_MES_UNKNOWN,  7 },
    { L"linear",        AUO_MES_UNKNOWN,  8 },
    { L"log100",        AUO_MES_UNKNOWN,  9 },
    { L"log100-sqrt10", AUO_MES_UNKNOWN, 10 },
    { L"iec61966",      AUO_MES_UNKNOWN, 11 },
    { L"bt1361",        AUO_MES_UNKNOWN, 12 },
    { L"srgb",          AUO_MES_UNKNOWN, 13 },
    { L"bt2020-10",     AUO_MES_UNKNOWN, 14 },
    { L"bt2020-12",     AUO_MES_UNKNOWN, 15 },
    { L"smpte2084",     AUO_MES_UNKNOWN, 16 },
    { L"smpte428",      AUO_MES_UNKNOWN, 17 },
    { L"hlg",           AUO_MES_UNKNOWN, 18 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_colormatrix[] = {
    { L"undef",       AUO_OPTION_VUI_UNDEF, 2  },
    { L"auto",        AUO_OPTION_VUI_AUTO, COLOR_MATRIX_AUTO  },
    { L"bt709",       AUO_MES_UNKNOWN, 1  },
    { L"identity",    AUO_MES_UNKNOWN, 0  },
    //{ L"smpte170m",   AUO_MES_UNKNOWN,  3 },
    { L"fcc",         AUO_MES_UNKNOWN,  4 },
    { L"bt470bg",     AUO_MES_UNKNOWN,  5 },
    { L"bt601",       AUO_MES_UNKNOWN,  6 },
    { L"smpte240",    AUO_MES_UNKNOWN,  7 },
    { L"ycgco",       AUO_MES_UNKNOWN,  8 },
    { L"bt2020-ncl",  AUO_MES_UNKNOWN,  9 },
    { L"bt2020-cl",   AUO_MES_UNKNOWN, 10 },
    { L"smpte2085",   AUO_MES_UNKNOWN, 11 },
    { L"chroma-ncl",  AUO_MES_UNKNOWN, 12 },
    { L"chroma-cl",   AUO_MES_UNKNOWN, 13 },
    { L"ictcp",       AUO_MES_UNKNOWN, 14 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const ENC_OPTION_STR list_videoformat[] = {
    { _T("undef"),     AUO_OPTION_VUI_UNDEF, L"指定なし"  },
    { _T("ntsc"),      AUO_MES_UNKNOWN,      L"ntsc"      },
    { _T("component"), AUO_MES_UNKNOWN,      L"component" },
    { _T("pal"),       AUO_MES_UNKNOWN,      L"pal"       },
    { _T("secam"),     AUO_MES_UNKNOWN,      L"secam"     },
    { _T("mac"),       AUO_MES_UNKNOWN,      L"mac"       },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const ENC_OPTION_STR list_log_type[] = {
    { _T("none"),    AUO_MES_UNKNOWN, L"none"    },
    { _T("error"),   AUO_MES_UNKNOWN, L"error"   },
    { _T("warning"), AUO_MES_UNKNOWN, L"warning" },
    { _T("info"),    AUO_MES_UNKNOWN, L"info"    },
    { _T("debug"),   AUO_MES_UNKNOWN, L"debug"   },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};

#pragma pack(push,1)
typedef struct {
    int x;
    int y;
} INT2;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    float x;
    float y;
} FLOAT2;
#pragma pack(pop)

//x264パラメータ構造体
//guiExで使いやすいよう、適当に
//並び順に意味はない
#pragma pack(push,1)
typedef struct {
    int     preset;            //enc-mode
    int     bit_depth;           //bit-depth
    int     output_csp;        //color_format
    int     profile;
    int     pass;
    int     qp;                  //q
    int     bitrate;             //tbr (bitrate)
    int     rc;                  //rc
    int     aq;
    int     color_primaries; //--color-primaries
    int     color_range; //--color_range
    int     enable_cdef; //--enable-cdef
    int     enable_dlf; //--enable-dlf
    int     enable_hdr; //--enable-hdr
    int     enable_mfmv;  //--enable-mfmv (on,off,default)
    int     enable_overlays; //--enable-overlays
    int     enable_restoration; //--enable-restoration
    int     enable_stat_report;
    int     enable_tf;
    int     enable_tpl_la;
    int     enable_variance_boost;
    int     fast_decode;
    int     film_grain; //--film-grain
    int     hierarchical_levels; //hierarchical-levels
    int     intra_refresh_type;  //irefresh-type
    int     keyint;        //keyint
    int     lp;         //lp (LogicalProcessorNumber)
    int     lookahead;
    int     luminance_qp_bias; //--luminance-qp-bias
    int     matrix_coefficients; //--matrix-coefficients
    int     max_qp;
    int     maxsection_pct; //--maxsection-pct
    int     min_qp;
    int     minsection_pct; //--minsection-pct
    int     overshoot_pct; //--overshoot-pct
    int     sharpness; // sharpness
    int     scd;        //scd (scene change detection)
    int     scm;        //scm (list_scm)
    int     tf_strength; // --tf-strength
    int     tile_rows;   //tile-rows
    int     tile_columns; //tile-columns
    int     transfer_characteristics; // --transfer-characteristics
    int     tune; //tune
    int     undershoot_pct; //--undershoot-pct
    int     variance_boost_strength; //--variance-boost-strength
    int     variance_octile; // --variance-octile
} CONF_ENC;
#pragma pack(pop)

static const wchar_t *get_chr_from_value(const CX_DESC_AUO *list, int v) {
    for (int i = 0; list[i].desc; i++)
        if (list[i].value == v)
            return list[i].desc;
    return L"unknown";
}

static int get_cx_index(const CX_DESC_AUO *list, int v) {
    for (int i = 0; list[i].desc; i++)
        if (list[i].value == v)
            return i;
    return 0;
}

static int get_cx_index(const CX_DESC_AUO *list, const wchar_t *chr) {
    for (int i = 0; list[i].desc; i++)
        if (0 == wcsicmp(list[i].desc, chr))
            return i;
    return 0;
}

static int get_cx_value(const CX_DESC_AUO *list, const wchar_t *chr) {
    for (int i = 0; list[i].desc; i++)
        if (0 == wcsicmp(list[i].desc, chr))
            return list[i].value;
    return 0;
}

static int get_value_from_chr(const CX_DESC_AUO *list, const wchar_t *chr) {
    for (int i = 0; list[i].desc; i++)
        if (wcsicmp(list[i].desc, chr) == 0)
            return list[i].value;
    return -1;
}

static const wchar_t *get_cx_desc(const CX_DESC_AUO *list, int v) {
    for (int i = 0; list[i].desc; i++)
        if (list[i].value == v)
            return list[i].desc;
    return nullptr;
}

const CX_DESC_AUO list_rc[] = {
    { L"CQP", AUO_MES_UNKNOWN,  0 },
    { L"CRF", AUO_MES_UNKNOWN, -1 },
    { L"VBR", AUO_MES_UNKNOWN,  1 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};

const CX_DESC_AUO list_on_off_default[] = {
    { L"-1: default", AUO_MES_UNKNOWN, -1 },
    { L"0: off", AUO_MES_UNKNOWN, 0 },
    { L"1: on", AUO_MES_UNKNOWN, 1 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_color_format[] = {
    { L"0: yuv400", AUO_MES_UNKNOWN, 0 },
    { L"1: yuv420", AUO_MES_UNKNOWN, 1 },
    { L"2: yuv422", AUO_MES_UNKNOWN, 2 },
    { L"3: yuv444", AUO_MES_UNKNOWN, 3 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_hierarchical_levels[] = {
    { L"0:  0B Pyramid", AUO_OPTION_HIERARCHICAL_LEVEL_0, 0 },
    { L"1:  1B Pyramid", AUO_OPTION_HIERARCHICAL_LEVEL_1, 1 },
    { L"2:  3B Pyramid", AUO_OPTION_HIERARCHICAL_LEVEL_2, 2 },
    { L"3:  7B Pyramid", AUO_OPTION_HIERARCHICAL_LEVEL_3, 3 },
    { L"4: 15B Pyramid", AUO_OPTION_HIERARCHICAL_LEVEL_4, 4 },
    { L"5: 31B Pyramid", AUO_OPTION_HIERARCHICAL_LEVEL_5, 5 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_chroma_mode[] = {
    { L"-1: default",                   AUO_OPTION_CHROMA_MODE_A, -1 },
    { L"0: Full chroma search",         AUO_OPTION_CHROMA_MODE_0,  0 },
    { L"1: Fast chroma search",         AUO_OPTION_CHROMA_MODE_1,  1 },
    { L"2: Chroma blind @ MD + CFL",    AUO_OPTION_CHROMA_MODE_2,  2 },
    { L"3: Chroma blind @ MD + no CFL", AUO_OPTION_CHROMA_MODE_3,  3 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_compound[] = {
    { L"-1: default",                 AUO_OPTION_COMPOUND_A, -1 },
    { L"0: off",                      AUO_OPTION_COMPOUND_0,  0 },
    { L"1: on (AVG/DIST/DIFF)",       AUO_OPTION_COMPOUND_1,  1 },
    { L"2: on (AVG/DIST/DIFF/WEDGE)", AUO_OPTION_COMPOUND_2,  2 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_hbd_md[] = {
    { L"0: off",     AUO_OPTION_HBD_MD_0, 0 },
    { L"1: partial", AUO_OPTION_HBD_MD_1, 1 },
    { L"2: full",    AUO_OPTION_HBD_MD_2, 2 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_intra_bcmode[] = {
    { L"-1: default", AUO_OPTION_INTRA_BCMODE_A, -1 },
    { L"0: off",      AUO_OPTION_INTRA_BCMODE_0,  0 },
    { L"1: slow",     AUO_OPTION_INTRA_BCMODE_1,  1 },
    { L"2: fast",     AUO_OPTION_INTRA_BCMODE_2,  2 },
    { L"3: fastest",  AUO_OPTION_INTRA_BCMODE_3,  3 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_sg_filter_mode[] = {
    { L"-1: default", AUO_OPTION_SG_FILTER_A, -1 },
    { L"0: off",      AUO_OPTION_SG_FILTER_0,  0 },
    { L"1: step 0",   AUO_OPTION_SG_FILTER_1,  1 },
    { L"2: step 1",   AUO_OPTION_SG_FILTER_2,  2 },
    { L"3: step 4",   AUO_OPTION_SG_FILTER_3,  3 },
    { L"4: step 16",  AUO_OPTION_SG_FILTER_4,  4 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_wn_filter_mode[] = {
    { L"-1: default", AUO_OPTION_WN_FILTER_MODE_A, -1 },
    { L"0: off",      AUO_OPTION_WN_FILTER_MODE_0,  0 },
    { L"1: 3-Tap",    AUO_OPTION_WN_FILTER_MODE_1,  1 },
    { L"2: 5-Tap",    AUO_OPTION_WN_FILTER_MODE_2,  2 },
    { L"3: 7-Tap",    AUO_OPTION_WN_FILTER_MODE_3,  3 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_bipred_3x3[] = {
    { L"-1: default", AUO_OPTION_BIPRED_3x3_A, -1 },
    { L"0: off",      AUO_OPTION_BIPRED_3x3_0,  0 },
    { L"1: full",     AUO_OPTION_BIPRED_3x3_1,  1 },
    { L"2: reduced",  AUO_OPTION_BIPRED_3x3_2,  2 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_pred_me[] = {
    { L"-1: default", AUO_OPTION_PRED_ME_A, -1 },
    { L"0: off",      AUO_OPTION_PRED_ME_0,  0 },
    { L"1: faster",   AUO_OPTION_PRED_ME_1,  1 },
    { L"2: ",         AUO_OPTION_PRED_ME_2,  2 },
    { L"3: ",         AUO_OPTION_PRED_ME_3,  3 },
    { L"4: ",         AUO_OPTION_PRED_ME_4,  4 },
    { L"5: slower",   AUO_OPTION_PRED_ME_5,  5 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_profile_av1[] = {
    { L"0: main",         AUO_MES_UNKNOWN, 0 },
    { L"1: high",         AUO_MES_UNKNOWN, 1 },
    { L"2: professional", AUO_MES_UNKNOWN, 2 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_obmc_level[] = {
    { L"-1: default", AUO_OPTION_OBMC_LEVEL_A, -1 },
    { L"0: off",      AUO_OPTION_OBMC_LEVEL_0,  0 },
    { L"1: full",     AUO_OPTION_OBMC_LEVEL_1,  1 },
    { L"2: fast",     AUO_OPTION_OBMC_LEVEL_2,  2 },
    { L"3: faster",   AUO_OPTION_OBMC_LEVEL_3,  3 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_mrp_level[] = {
    { L"-1: default", AUO_OPTION_MRP_LEVEL_A, -1 },
    { L"0: off",      AUO_OPTION_MRP_LEVEL_0,  0 },
    { L"1: full ",    AUO_OPTION_MRP_LEVEL_1,  1 },
    { L"2: Level 1",  AUO_OPTION_MRP_LEVEL_2,  2 },
    { L"3: Level 2",  AUO_OPTION_MRP_LEVEL_3,  3 },
    { L"7: Level 3",  AUO_OPTION_MRP_LEVEL_4,  4 },
    { L"5: Level 4",  AUO_OPTION_MRP_LEVEL_5,  5 },
    { L"6: Level 5",  AUO_OPTION_MRP_LEVEL_6,  6 },
    { L"7: Level 6",  AUO_OPTION_MRP_LEVEL_7,  7 },
    { L"8: Level 7",  AUO_OPTION_MRP_LEVEL_8,  8 },
    { L"9: Level 8",  AUO_OPTION_MRP_LEVEL_9,  9 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_scm[] = {
    { L"0: off",                     AUO_OPTION_SCM_0, 0 },
    { L"1: on",                      AUO_OPTION_SCM_1, 1 },
    { L"2: Content Based Detection", AUO_OPTION_SCM_2, 2 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_enc_mode[] = {
    { L"0 - best quality", AUO_OPTION_ENC_MODE_00,  0 },
    { L"1",                AUO_OPTION_ENC_MODE_01,  1 },
    { L"2",                AUO_OPTION_ENC_MODE_02,  2 },
    { L"3",                AUO_OPTION_ENC_MODE_03,  3 },
    { L"4",                AUO_OPTION_ENC_MODE_04,  4 },
    { L"5",                AUO_OPTION_ENC_MODE_05,  5 },
    { L"6",                AUO_OPTION_ENC_MODE_06,  6 },
    { L"7",                AUO_OPTION_ENC_MODE_07,  7 },
    { L"8",                AUO_OPTION_ENC_MODE_08,  8 },
    { L"9",                AUO_OPTION_ENC_MODE_09,  9 },
    { L"10",               AUO_OPTION_ENC_MODE_10, 10 },
    { L"11",               AUO_OPTION_ENC_MODE_11, 11 },
    { L"12",               AUO_OPTION_ENC_MODE_12, 12 },
    { L"13 - fast",        AUO_OPTION_ENC_MODE_13, 13 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_aq[] = {
    { L"0: off",                    AUO_OPTION_AQ_0, 0 },
    { L"1: variance base",          AUO_OPTION_AQ_1, 1 },
    { L"2: deltaq pred efficiency", AUO_OPTION_AQ_2, 2 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
const CX_DESC_AUO list_tune[] = {
    { L"0: VQ",    AUO_MES_UNKNOWN, 0 },
    { L"1: PSNR",  AUO_MES_UNKNOWN, 1 },
    { L"2: SSIM",  AUO_MES_UNKNOWN, 2 },
    { L"3: Image Quality",  AUO_MES_UNKNOWN, 3 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};

const CX_DESC_AUO list_palette[] = {
    { L"-1: default", AUO_OPTION_PALETTE_A, -1 },
    { L"0: off",      AUO_OPTION_PALETTE_0,  0 },
    { L"1 ",          AUO_OPTION_PALETTE_1,  1 },
    { L"2 ",          AUO_OPTION_PALETTE_2,  2 },
    { L"3 ",          AUO_OPTION_PALETTE_3,  3 },
    { L"4 ",          AUO_OPTION_PALETTE_3,  4 },
    { L"5 ",          AUO_OPTION_PALETTE_5,  5 },
    { L"6 ",          AUO_OPTION_PALETTE_6,  6 },
    { nullptr, AUO_MES_UNKNOWN, 0 }
};
typedef struct {
    TCHAR *long_name;
    TCHAR *short_name;
    DWORD type;
    const ENC_OPTION_STR *list;
    size_t p_offset;
} X264_OPTIONS;

enum {
    ARG_TYPE_UNKNOWN = 0,
    ARG_TYPE_LONG    = 1,
    ARG_TYPE_SHORT   = 2,
};

typedef struct CMD_ARG {
    int arg_type;       //LONGかSHORTか
    TCHAR *option_name;  //オプション名(最初の"--"なし)
    TCHAR *value;        //オプションの値
    BOOL value_had_dQB; //前後に'"'があったか
    BOOL ret;           //構造体に読み込まれたかどうか
    BOOL type_mediainfo; //MediaInfoの書式だったかどうか
} CMD_ARG;

bool ishighbitdepth(const CONF_ENC *enc);

void set_guiEx_auto_sar(int *sar_x, int *sar_y, int width, int height);

//コマンドラインの解析・生成
int set_cmd(CONF_ENC *cx, const TCHAR *cmd, const bool ignore_parse_err);
int parse_cmd(CONF_ENC *cx, const TCHAR *cmd, const bool ignore_parse_err);
tstring gen_cmd(const CONF_ENC *cx, bool save_disabled_prm);
CONF_ENC get_default_prm();
void set_ex_stg_ptr(guiEx_settings *_ex_stg);
void set_auto_colormatrix(CONF_ENC *cx, int height);

#endif //_AUO_OPTIONS_H_
