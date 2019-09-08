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
    OUT_CSP_YV12,
    OUT_CSP_NV16,
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

const ENC_OPTION_STR list_rc[] = {
    { "CQP",  L"CQP" },
    { "ABR",  L"ABR" },
    { "ABR",  L"ABR" },
    { "CVBR", L"CVBR"  },
    { NULL, NULL }
};
const ENC_OPTION_STR list_enc_mode[] = {
    { "0 - best quality",  L"0 - best quality" },
    { "1",  L"1" },
    { "2",  L"2" },
    { "3",  L"3" },
    { "4",  L"4" },
    { "5",  L"5" },
    { "6",  L"6" },
    { "7",  L"7" },
    { "8 - fast",  L"8 - fast" },
    { NULL, NULL }
};
const ENC_OPTION_STR list_aq[] = {
    { "off",  L"off" },
    { "variance base",  L"variance base" },
    { "Deltaq pred efficiency",  L"Deltaq pred efficiency " },
    { NULL, NULL }
};
const ENC_OPTION_STR list_scm[] = {
    { "off",  L"off" },
    { "on",   L"on" },
    { "Content Based",  L"Content Based" },
    { NULL, NULL }
};

//x264のinput-cspとして使用するもの
//OUT_CSP_NV12, OUT_CSP_YUV444, OUT_CSP_RGB に合わせる
static const char * const specify_csp[] = {
    "yv12", //OUT_CSP_YV12
    "nv16", //OUT_CSP_NV16
    "i444", //OUT_CSP_YUV444
    "rgb"   //OUT_CSP_RGB
};
//文字列を引数にとるオプションの引数リスト
//OUT_CSP_NV12, OUT_CSP_YUV444, OUT_CSP_RGB に合わせる
const ENC_OPTION_STR list_output_csp[] = {
    { "i420", L"i420" },
    { "i422", L"i422" },
    { "i444", L"i444" },
    { "rgb",  L"rgb"  },
    { NULL, NULL }
};
const ENC_OPTION_STR list_input_range[] = {
    { "auto", L"auto" },
    { "pc",   L"pc" },
    { NULL, NULL }
};
const ENC_OPTION_STR list_colorprim[] = {
    { "undef",     L"指定なし"  },
    { "auto",      L"自動"      },
    { "bt709",     L"bt709"     },
    { "smpte170m", L"smpte170m" },
    { "bt470m",    L"bt470m"    },
    { "bt470bg",   L"bt470bg"   },
    { "smpte240m", L"smpte240m" },
    { "film",      L"film"      },
    { "bt2020",    L"bt2020"    },
    { "smpte428",  L"smpte428"  },
    { "smpte431",  L"smpte431"  },
    { "smpte432",  L"smpte432"  },
    { NULL, NULL }
};
const ENC_OPTION_STR list_transfer[] = {
    { "undef",        L"指定なし"     },
    { "auto",         L"自動"         },
    { "bt709",        L"bt709"        },
    { "smpte170m",    L"smpte170m"    },
    { "bt470m",       L"bt470m"       },
    { "bt470bg",      L"bt470bg"      },
    { "smpte240m",    L"smpte240m"    },
    { "linear",       L"linear"       },
    { "log100",       L"log100"       },
    { "log316",       L"log316"       },
    { "iec61966-2-4", L"iec61966-2-4" },
    { "bt1361e",      L"bt1361e"      },
    { "iec61966-2-1", L"iec61966-2-1" },
    { "bt2020-10",    L"bt2020-10"    },
    { "bt2020-12",    L"bt2020-12"    },
    { "smpte2084",    L"smpte2084"    },
    { "smpte428",     L"smpte428"     },
    { "arib-std-b67", L"arib-std-b67" },
    { NULL, NULL }
};
const ENC_OPTION_STR list_colormatrix[] = {
    { "undef",     L"指定なし"  },
    { "auto",      L"自動"      },
    { "bt709",     L"bt709"     },
    { "smpte170m", L"smpte170m" },
    { "bt470bg",   L"bt470bg"   },
    { "smpte240m", L"smpte240m" },
    { "YCgCo",     L"YCgCo"     },
    { "fcc",       L"fcc"       },
    { "GBR",       L"GBR"       },
    { "bt2020nc",  L"bt2020nc"  },
    { "bt2020c",   L"bt2020c"   },
    { "smpte2085", L"smpte2085" },
    { "chroma-derived-nc", L"chroma-derived-nc" },
    { "chroma-derived-c",  L"chroma-derived-c" },
    { "ICtCp",     L"ICtCp" },
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

//色についてのオプション設定(0がデフォルトとなるよう、x264とは並び順が異なる)
//まあGUIで順番なんてどうでも…
enum {
    COLOR_MATRIX_DEFAULT   = 0,
    COLOR_MATRIX_AUTO      = 1,
    COLOR_MATRIX_HD        = 2,
    COLOR_MATRIX_SD        = 3,
};
const int COLOR_MATRIX_THRESHOLD = 720;

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
    int     enc_mode;            //enc-mode
    int     bit_depth;           //bit-depth
    int     output_csp;          //output-csp
    int     qp;                  //q
    int     rc;                  //rc
    int     hierarchical_levels; //hierarchical-levels
    int     intra_period;        //intra-period
    int     intra_refresh_type;  //irefresh-type
    int     aq;
    BOOL    use_default_me_hme;  //use-default-me-hme
    BOOL    in_loop_me; //in-loop-me
    BOOL    local_warp; //local-warp
    BOOL    ext_block;  //ext-block
    int     scm;        //scm
    int     search_w;   //search_w
    int     search_h;   //search_h
    int     lad;        //lad (lookahead distance)
    BOOL    scd;        //scd (scene change detection)
    int     lp;         //lp (LogicalProcessorNumber)
    BOOL    sharp;      //improve sharpness
    int     tile_rows;   //tile-rows
    int     tile_columns; //tile-columns
} CONF_ENCODER;
#pragma pack(pop)

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

#endif //_AUO_OPTIONS_H_
