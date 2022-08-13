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

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <Math.h>
#include <limits.h>
#include <vector>
#include <string>
#include <sstream>

#include "h264_level.h"
#include "auo_util.h"
#include "auo_conf.h"
#include "auo_options.h"

#include "shellapi.h"
#pragma comment(lib, "Shell32.lib")


static guiEx_settings *ex_stg = nullptr;

void set_ex_stg_ptr(guiEx_settings *_ex_stg) {
    ex_stg = _ex_stg;
}

void set_guiEx_auto_sar(int *sar_x, int *sar_y, int width, int height) {
    if (width > 0 && height > 0 && *sar_x < 0 && *sar_y < 0) {
        int x = -1 * *sar_x * height;
        int y = -1 * *sar_y * width;
        if (abs(y - x) > -16 * *sar_y) {
            int gcd = get_gcd(x, y);
            *sar_x = x / gcd;
            *sar_y = y / gcd;
        } else {
            *sar_x = *sar_y = 1;
        }
    } else if (*sar_x * *sar_y < 0) {
        *sar_x = *sar_y = 0;
    }
}

std::vector<std::wstring> sep_cmd(const std::wstring &cmd) {
    std::vector<std::wstring> args;
    int argc = 0;
    auto ptr = CommandLineToArgvW(cmd.c_str(), &argc);
    for (int i = 0; i < argc; i++) {
        args.push_back(ptr[i]);
    }
    args.push_back(L"");
    LocalFree(ptr);
    return std::move(args);
}

std::vector<std::string> sep_cmd(const std::string &cmd) {
    std::vector<std::string> args;
    std::wstring wcmd = char_to_wstring(cmd);
    for (const auto &warg : sep_cmd(wcmd)) {
        args.push_back(wstring_to_string(warg));
    }
    return std::move(args);
}

int parse_one_option(CONF_ENCODER *cx, const char *option_name, const std::vector<std::string>& argv, int &i, int nArgNum) {
#define IS_OPTION(x) (std::string(x) == option_name)
    auto to_int = [](int *value, const std::string& argv) {
        try {
            *value = std::stoi(argv);
        } catch (...) {
            return 1;
        }
        return 0;
    };
#define OPT_NUM(str, val) \
    if (IS_OPTION(str)) { \
        i++; \
        return to_int(&cx->val, argv[i]); \
    }

    OPT_NUM("preset", preset);
    OPT_NUM("input-depth", bit_depth);
    if (IS_OPTION("crf")) {
        i++;
        int ret = to_int(&cx->qp, argv[i]);
        cx->rc = get_cx_value(list_rc, L"CRF");
        return ret;
    }
    OPT_NUM("rc", rc);
    OPT_NUM("q", qp);
    OPT_NUM("color-format", output_csp);
    OPT_NUM("profile", profile);
    OPT_NUM("pass", pass);
    OPT_NUM("tbr", bitrate);
    OPT_NUM("lp", lp);

    OPT_NUM("aq-mode", aq);
    OPT_NUM("bias-pct", bias_pct);
    OPT_NUM("color-primaries", color_primaries);
    OPT_NUM("color-range", color_range);
    OPT_NUM("enable-cdef", enable_cdef);
    OPT_NUM("enable-dlf", enable_dlf);
    OPT_NUM("enable-hdr", enable_hdr);
    OPT_NUM("enable-mfmv", enable_mfmv);
    OPT_NUM("enable-overlays", enable_overlays);
    OPT_NUM("enable-restoration", enable_restoration);
    OPT_NUM("enable-stat-report", enable_stat_report);
    OPT_NUM("enable-tf", enable_tf);
    OPT_NUM("enable-tpl-la", enable_tpl_la);
    OPT_NUM("fast-decode", fast_decode);
    OPT_NUM("film-grain", film_grain);
    OPT_NUM("hierarchical-levels", hierarchical_levels);
    OPT_NUM("irefresh-type", intra_refresh_type);
    OPT_NUM("keyint", keyint);
    OPT_NUM("matrix-coefficients", matrix_coefficients);
    OPT_NUM("max-qp", max_qp);
    OPT_NUM("maxsection-pct", maxsection_pct);
    OPT_NUM("min-qp", min_qp);
    OPT_NUM("minsection-pct", minsection_pct);
    OPT_NUM("overshoot-pct", overshoot_pct);
    OPT_NUM("rmv", rmv);
    OPT_NUM("scd", scd);
    OPT_NUM("scm", scm);
    OPT_NUM("tile-rows", tile_rows);
    OPT_NUM("tile-columns", tile_columns);
    OPT_NUM("transfer-characteristics", transfer_characteristics);
    OPT_NUM("tune", tune);
    OPT_NUM("undershoot-pct", undershoot_pct);
    return 1;
#undef OPT_NUM
#undef IS_OPTION
}

int set_cmd(CONF_ENCODER *cx, const char *cmd, const bool ignore_parse_err) {
    auto args = sep_cmd(cmd);
    for (int i = 0; i < args.size(); i++) {
        const char *option_name = nullptr;
        if (args[i][0] == '|') {
            break;
        } else if (args[i][0] == '-' && args[i][1] == 'q') {
            option_name = &args[i][1];
        } else if (args[i][0] == '-' && args[i][1] == '-') {
            option_name = &args[i][2];
        } else {
            if (ignore_parse_err) continue;
            return 1;
        }
        if (args[i].length() > 0) {
            auto sts = parse_one_option(cx, option_name, args, i, (int)args.size());
            if (!ignore_parse_err && sts != 0) {
                return sts;
            }
        }
    }
    return 0;
}

CONF_ENCODER get_default_prm() {
    CONF_ENCODER prm;
    memset(&prm, 0, sizeof(prm));
    set_cmd(&prm, ex_stg->s_enc.default_cmd, true);
    return prm;
}

int parse_cmd(CONF_ENCODER *cx, const char *cmd, const bool ignore_parse_err) {
    *cx = get_default_prm();
    return set_cmd(cx, cmd, ignore_parse_err);
}

std::string gen_cmd(const CONF_ENCODER *cx, bool save_disabled_prm) {
    std::stringstream cmd;
    CONF_ENCODER encPrmDefault = get_default_prm();
#define OPT_NUM(str, opt) if ((cx->opt) != (encPrmDefault.opt)) cmd << " --" << (str) << " " << (int)(cx->opt);

    OPT_NUM("preset", preset);
    OPT_NUM("input-depth", bit_depth);
    if (cx->rc == get_cx_value(list_rc, L"CRF")) {
        cmd << " --crf " << (int)(cx->qp);
    } else {
        OPT_NUM("rc", rc);
        if ((cx->qp) != (encPrmDefault.qp)) cmd << " -q " << (int)(cx->qp);
    }
    OPT_NUM("color-format", output_csp);
    OPT_NUM("profile", profile);
    OPT_NUM("pass", pass);
    OPT_NUM("tbr", bitrate);
    OPT_NUM("lp", lp);

    if (cx->rc == get_cx_value(list_rc, L"CQP")) {
        cmd << " --aq-mode " << 0;
    } else if (cx->rc == get_cx_value(list_rc, L"CRF")) {
        if (cx->aq != 0) OPT_NUM("aq-mode", aq);
    } else {
        OPT_NUM("aq-mode", aq);
    }
    OPT_NUM("bias-pct", bias_pct);
    OPT_NUM("color-primaries", color_primaries);
    OPT_NUM("color-range", color_range);
    OPT_NUM("enable-cdef", enable_cdef);
    OPT_NUM("enable-dlf", enable_dlf);
    OPT_NUM("enable-hdr", enable_hdr);
    OPT_NUM("enable-mfmv", enable_mfmv);
    OPT_NUM("enable-overlays", enable_overlays);
    OPT_NUM("enable-restoration", enable_restoration);
    OPT_NUM("enable-stat-report", enable_stat_report);
    OPT_NUM("enable-tf", enable_tf);
    OPT_NUM("enable-tpl-la", enable_tpl_la);
    OPT_NUM("fast-decode", fast_decode);
    OPT_NUM("film-grain", film_grain);
    OPT_NUM("hierarchical-levels", hierarchical_levels);
    OPT_NUM("irefresh-type", intra_refresh_type);
    OPT_NUM("keyint", keyint);
    OPT_NUM("matrix-coefficients", matrix_coefficients);
    OPT_NUM("max-qp", max_qp);
    OPT_NUM("maxsection-pct", maxsection_pct);
    OPT_NUM("min-qp", min_qp);
    OPT_NUM("minsection-pct", minsection_pct);
    OPT_NUM("overshoot-pct", overshoot_pct);
    OPT_NUM("rmv", rmv);
    OPT_NUM("scd", scd);
    OPT_NUM("scm", scm);
    OPT_NUM("tile-rows", tile_rows);
    OPT_NUM("tile-columns", tile_columns);
    OPT_NUM("transfer-characteristics", transfer_characteristics);
    OPT_NUM("tune", tune);
    OPT_NUM("undershoot-pct", undershoot_pct);

    return cmd.str();
}

void set_auto_colormatrix(CONF_ENCODER *cx, int height) {
    if (cx->matrix_coefficients == COLOR_MATRIX_AUTO)
        cx->matrix_coefficients = (height >= COLOR_MATRIX_THRESHOLD) ? get_cx_value(list_colormatrix, L"bt709") : get_cx_value(list_colormatrix, L"bt601");
    if (cx->color_primaries == COLOR_MATRIX_AUTO)
        cx->color_primaries = (height >= COLOR_MATRIX_THRESHOLD) ? get_cx_value(list_colorprim, L"bt709") : get_cx_value(list_colormatrix, L"bt601");
    if (cx->transfer_characteristics == COLOR_MATRIX_AUTO)
        cx->transfer_characteristics = (height >= COLOR_MATRIX_THRESHOLD) ? get_cx_value(list_transfer, L"bt709") : get_cx_value(list_colormatrix, L"bt601");
}