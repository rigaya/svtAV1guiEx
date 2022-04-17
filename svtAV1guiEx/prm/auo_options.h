// -----------------------------------------------------------------------------------------
// svtAV1guiEx by rigaya
// -----------------------------------------------------------------------------------------
// The MIT License
//
// Copyright (c) 2019 rigaya
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

#include <Windows.h>
#include <vector>
#include <string>
#include <limits>

#include "auo.h"
#include "auo_settings.h"

//エンコードモード
enum {
    X264_RC_QP = 0,
    X264_RC_BITRATE,
};

//QPの最大値
const int X264_QP_MAX_8BIT  = 69;
const int X264_QP_MAX_10BIT = 81;

//差がこのくらいなら等しいとみなす(オプション用なのでこのくらいで十分)
const float EPS_FLOAT = 1.0e-4f;

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
    OUT_CSP_NV12
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
static const char * const specify_csp[] = {
    "yuv400", //OUT_CSP_YUV400
    "yuv420", //OUT_CSP_YV12
    "yuv422", //OUT_CSP_YUV422
    "yuv444", //OUT_CSP_YUV444
    "rgb"   //OUT_CSP_RGB
};
//文字列を引数にとるオプションの引数リスト
//OUT_CSP_NV12, OUT_CSP_YUV444, OUT_CSP_RGB に合わせる
const ENC_OPTION_STR list_output_csp[] = {
    { "yuv400", L"yuv400" },
    { "yuv420", L"yuv420" },
    { "yuv422", L"yuv422" },
    { "yuv444", L"yuv444" },
    { "rgb",  L"rgb"  },
    { NULL, NULL }
};

typedef struct CX_DESC {
    const TCHAR *desc;
    int value;
} CX_DESC;

enum {
    COLOR_MATRIX_AUTO = 0,
};
const int COLOR_MATRIX_THRESHOLD = 720;

const CX_DESC list_color_range[] = {
    { "auto",  0 },
    { "pc",    1 },
    { nullptr, 0 }
};
const CX_DESC list_colorprim[] = {
    { "undef",     2   },
    { "auto",      COLOR_MATRIX_AUTO   },
    { "bt709",     1   },
    //{ "smpte170m", 3 },
    { "bt470m",    4   },
    { "bt470bg",   5   },
    { "bt601",     6   },
    { "smpte240",  7   },
    { "film",      8   },
    { "bt2020",    9   },
    { "xyz",       10  },
    { "smpte431",  11  },
    { "smpte432",  12  },
    { "ebu3213",   22  },
    { NULL, NULL }
};
const CX_DESC list_transfer[] = {
    { "undef",        2  },
    { "auto",         COLOR_MATRIX_AUTO  },
    { "bt709",        1  },
    //{ "smpte170m",    3    },
    { "bt470m",       4  },
    { "bt470bg",      5  },
    { "bt601",        6  },
    { "smpte240",     7  },
    { "linear",       8  },
    { "log100",       9  },
    { "log100-sqrt10", 10 },
    { "iec61966",     11 },
    { "bt1361",       12 },
    { "srgb",         13 },
    { "bt2020-10",    14 },
    { "bt2020-12",    15 },
    { "smpte2084",    16 },
    { "smpte428",     17 },
    { "hlg",          18 },
    { NULL, NULL }
};
const CX_DESC list_colormatrix[] = {
    { "undef",     2  },
    { "auto",      COLOR_MATRIX_AUTO  },
    { "bt709",     1  },
    { "identity",  0  },
    //{ "smpte170m", 3 },
    { "fcc",       4  },
    { "bt470bg",   5  },
    { "bt601",     6  },
    { "smpte240",  7  },
    { "ycgco",     8  },
    { "bt2020-ncl",   9 },
    { "bt2020-cl",   10 },
    { "smpte2085",   11 },
    { "chroma-ncl",  12 },
    { "chroma-cl",   13 },
    { "ictcp",       14 },
    { NULL, NULL }
};
const ENC_OPTION_STR list_videoformat[] = {
    { "undef",     L"指定なし"  },
    { "ntsc",      L"ntsc"      },
    { "component", L"component" },
    { "pal",       L"pal"       },
    { "secam",     L"secam"     },
    { "mac",       L"mac"       },
    { NULL, NULL }
};
const ENC_OPTION_STR list_log_type[] = {
    { "none",    L"none"    },
    { "error",   L"error"   },
    { "warning", L"warning" },
    { "info",    L"info"    },
    { "debug",   L"debug"   },
    { NULL, NULL }
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
    int     bias_pct; //--bias-pct
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
    int     film_grain; //--film-grain
    int     hierarchical_levels; //hierarchical-levels
    int     intra_refresh_type;  //irefresh-type
    int     keyint;        //keyint
    int     lp;         //lp (LogicalProcessorNumber)
    int     matrix_coefficients; //--matrix-coefficients
    int     max_qp;
    int     maxsection_pct; //--maxsection-pct
    int     min_qp;
    int     minsection_pct; //--minsection-pct
    int     overshoot_pct; //--overshoot-pct
    int     rmv;        //--rmv
    int     scd;        //scd (scene change detection)
    int     scm;        //scm (list_scm)
    int     tile_rows;   //tile-rows
    int     tile_columns; //tile-columns
    int     transfer_characteristics; // --transfer-characteristics
    int     tune; //tune
    int     undershoot_pct; //--undershoot-pct
} CONF_ENCODER;
#pragma pack(pop)

static const TCHAR *get_chr_from_value(const CX_DESC *list, int v) {
    for (int i = 0; list[i].desc; i++)
        if (list[i].value == v)
            return list[i].desc;
    return "unknown";
}

static int get_cx_index(const CX_DESC *list, int v) {
    for (int i = 0; list[i].desc; i++)
        if (list[i].value == v)
            return i;
    return 0;
}

static int get_cx_index(const CX_DESC *list, const TCHAR *chr) {
    for (int i = 0; list[i].desc; i++)
        if (0 == stricmp(list[i].desc, chr))
            return i;
    return 0;
}

static int get_cx_value(const CX_DESC *list, const TCHAR *chr) {
    for (int i = 0; list[i].desc; i++)
        if (0 == stricmp(list[i].desc, chr))
            return list[i].value;
    return 0;
}

static int get_value_from_chr(const CX_DESC *list, const TCHAR *chr) {
    for (int i = 0; list[i].desc; i++)
        if (stricmp(list[i].desc, chr) == 0)
            return list[i].value;
    return -1;
}

static const TCHAR *get_cx_desc(const CX_DESC *list, int v) {
    for (int i = 0; list[i].desc; i++)
        if (list[i].value == v)
            return list[i].desc;
    return nullptr;
}

const CX_DESC list_rc[] = {
    { "CQP",  0 },
    { "CRF", -1 },
    { "VBR",  1 },
    { nullptr, 0 }
};

const CX_DESC list_on_off_default[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: on", 1 },
    { nullptr, 0 }
};
const CX_DESC list_color_format[] = {
    { "0: yuv400", 0 },
    { "1: yuv420", 1 },
    { "2: yuv422", 2 },
    { "3: yuv444", 3 },
    { nullptr, 0 }
};
const CX_DESC list_hierarchical_levels[] = {
    { "0:  0B Pyramid", 0 },
    { "1:  1B Pyramid", 1 },
    { "2:  3B Pyramid", 2 },
    { "3:  7B Pyramid", 3 },
    { "4: 15B Pyramid", 4 },
    { "5: 31B Pyramid", 5 },
    { nullptr, 0 }
};
const CX_DESC list_chroma_mode[] = {
    { "-1: default", -1 },
    { "0: Full chroma search", 0 },
    { "1: Fast chroma search", 1 },
    { "2: Chroma blind @ MD + CFL", 2 },
    { "3: Chroma blind @ MD + no CFL", 3 },
    { nullptr, 0 }
};
const CX_DESC list_compound[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: on (AVG/DIST/DIFF)", 1 },
    { "2: on (AVG/DIST/DIFF/WEDGE)", 2 },
    { nullptr, 0 }
};
const CX_DESC list_hbd_md[] = {
    { "0: off", 0 },
    { "1: partial", 1 },
    { "2: full", 2 },
    { nullptr, 0 }
};
const CX_DESC list_intra_bcmode[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: slow", 1 },
    { "2: fast", 2 },
    { "3: fastest", 3 },
    { nullptr, 0 }
};
const CX_DESC list_sg_filter_mode[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: step 0", 1 },
    { "2: step 1", 2 },
    { "3: step 4", 3 },
    { "4: step 16", 4 },
    { nullptr, 0 }
};
const CX_DESC list_wn_filter_mode[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: 3-Tap", 1 },
    { "2: 5-Tap", 2 },
    { "3: 7-Tap", 3 },
    { nullptr, 0 }
};
const CX_DESC list_bipred_3x3[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: full", 1 },
    { "2: reduced", 2 },
    { nullptr, 0 }
};
const CX_DESC list_pred_me[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: faster", 1 },
    { "2: ", 2 },
    { "3: ", 3 },
    { "4: ", 4 },
    { "5: slower", 5 },
    { nullptr, 0 }
};
const CX_DESC list_profile_av1[] = {
    { "0: main", 0 },
    { "1: high", 1 },
    { "2: professional", 2 },
    { nullptr, 0 }
};
const CX_DESC list_obmc_level[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: full", 1 },
    { "2: fast", 2 },
    { "3: faster", 3 },
    { nullptr, 0 }
};
const CX_DESC list_mrp_level[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1: full ", 1 },
    { "2: Level 1", 2 },
    { "3: Level 2", 3 },
    { "7: Level 3", 4 },
    { "5: Level 4", 5 },
    { "6: Level 5", 6 },
    { "7: Level 6", 7 },
    { "8: Level 7", 8 },
    { "9: Level 8", 9 },
    { nullptr, 0 }
};
const CX_DESC list_scm[] = {
    { "0: off", 0 },
    { "1: on", 1 },
    { "2: Content Based Detection", 2 },
    { nullptr, 0 }
};
const CX_DESC list_enc_mode[] = {
    { "0 - best quality",  0 },
    { "1",  1 },
    { "2",  2 },
    { "3",  3 },
    { "4",  4 },
    { "5",  5 },
    { "6",  6 },
    { "7",  7 },
    { "8",  8 },
    { "9",  9 },
    { "10",  10 },
    { "11",  11 },
    { "12 - fast",  12 },
    { NULL, NULL }
};
const CX_DESC list_aq[] = {
    { "0: off",  0 },
    { "1: variance base",  1 },
    { "2: deltaq pred efficiency",  2 },
    { NULL, NULL }
};
const CX_DESC list_tune[] = {
    { "0: VQ",    0 },
    { "1: ssim",  1 },
    { NULL, NULL }
};

const CX_DESC list_palette[] = {
    { "-1: default", -1 },
    { "0: off", 0 },
    { "1 ", 1 },
    { "2 ", 2 },
    { "3 ", 3 },
    { "4 ", 4 },
    { "5 ", 5 },
    { "6 ", 6 },
    { NULL, NULL }
};
typedef struct {
    char *long_name;
    char *short_name;
    DWORD type;
    const ENC_OPTION_STR *list;
    size_t p_offset;
} X264_OPTIONS;

enum {
    ARG_TYPE_UNKNOWN = 0,
    ARG_TYPE_LONG    = 1,
    ARG_TYPE_SHORT   = 2,
};

typedef struct {
    int arg_type;       //LONGかSHORTか
    char *option_name;  //オプション名(最初の"--"なし)
    char *value;        //オプションの値
    BOOL value_had_dQB; //前後に'"'があったか
    BOOL ret;           //構造体に読み込まれたかどうか
    BOOL type_mediainfo; //MediaInfoの書式だったかどうか
} CMD_ARG;

void set_guiEx_auto_sar(int *sar_x, int *sar_y, int width, int height);

//コマンドラインの解析・生成
int set_cmd(CONF_ENCODER *cx, const char *cmd, const bool ignore_parse_err);
int parse_cmd(CONF_ENCODER *cx, const char *cmd, const bool ignore_parse_err);
std::string gen_cmd(const CONF_ENCODER *cx, bool save_disabled_prm);
CONF_ENCODER get_default_prm();
void set_ex_stg_ptr(guiEx_settings *_ex_stg);
void set_auto_colormatrix(CONF_ENCODER *cx, int height);

#endif //_AUO_OPTIONS_H_
