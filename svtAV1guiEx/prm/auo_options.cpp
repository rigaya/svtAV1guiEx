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
#include <iomanip>

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

int parse_one_option(CONF_ENC *cx, const TCHAR *option_name, const std::vector<tstring>& argv, int &i, [[maybe_unused]] int nArgNum) {
#define IS_OPTION(x) (tstring(x) == option_name)
    auto to_int = [](int *value, const tstring& argv) {
        try {
            *value = std::stoi(argv);
        } catch (...) {
            return 1;
        }
        return 0;
    };
    auto to_float = [](float *value, const tstring& argv) {
        try {
            *value = std::stof(argv);
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
#define OPT_FLOAT(str, val) \
    if (IS_OPTION(str)) { \
        i++; \
        return to_float(&cx->val, argv[i]); \
    }

    OPT_NUM(_T("preset"), preset);
    OPT_NUM(_T("input-depth"), bit_depth);
    if (IS_OPTION(_T("crf"))) {
        i++;
        int ret = to_float(&cx->qp, argv[i]);
        cx->rc = get_cx_value(list_rc, L"CRF");
        return ret;
    }
    OPT_NUM(_T("rc"), rc);
    OPT_FLOAT(_T("q"), qp);
    OPT_NUM(_T("color-format"), output_csp);
    OPT_NUM(_T("profile"), profile);
    OPT_NUM(_T("pass"), pass);
    OPT_NUM(_T("tbr"), bitrate);
    OPT_NUM(_T("lp"), lp);

    OPT_NUM(_T("aq-mode"), aq);
    OPT_NUM(_T("color-primaries"), color_primaries);
    OPT_NUM(_T("color-range"), color_range);
    OPT_NUM(_T("enable-cdef"), enable_cdef);
    OPT_NUM(_T("enable-dlf"), enable_dlf);
    OPT_NUM(_T("enable-hdr"), enable_hdr);
    OPT_NUM(_T("enable-mfmv"), enable_mfmv);
    OPT_NUM(_T("enable-overlays"), enable_overlays);
    OPT_NUM(_T("enable-restoration"), enable_restoration);
    OPT_NUM(_T("enable-stat-report"), enable_stat_report);
    OPT_NUM(_T("enable-tf"), enable_tf);
    OPT_NUM(_T("enable-tpl-la"), enable_tpl_la);
    OPT_NUM(_T("enable-variance-boost"), enable_variance_boost);
    OPT_NUM(_T("fast-decode"), fast_decode);
    OPT_NUM(_T("film-grain"), film_grain);
    OPT_NUM(_T("hierarchical-levels"), hierarchical_levels);
    OPT_NUM(_T("irefresh-type"), intra_refresh_type);
    OPT_NUM(_T("keyint"), keyint);
    OPT_NUM(_T("lookahead"), lookahead);
    OPT_NUM(_T("luminance-qp-bias"), luminance_qp_bias);
    OPT_NUM(_T("matrix-coefficients"), matrix_coefficients);
    OPT_NUM(_T("max-qp"), max_qp);
    OPT_NUM(_T("maxsection-pct"), maxsection_pct);
    OPT_NUM(_T("min-qp"), min_qp);
    OPT_NUM(_T("minsection-pct"), minsection_pct);
    OPT_NUM(_T("overshoot-pct"), overshoot_pct);
    OPT_NUM(_T("sharpness"), sharpness);
    OPT_NUM(_T("scd"), scd);
    OPT_NUM(_T("scm"), scm);
    OPT_NUM(_T("tf-strength"), tf_strength);
    OPT_NUM(_T("tile-rows"), tile_rows);
    OPT_NUM(_T("tile-columns"), tile_columns);
    OPT_NUM(_T("transfer-characteristics"), transfer_characteristics);
    OPT_NUM(_T("tune"), tune);
    OPT_NUM(_T("undershoot-pct"), undershoot_pct);
    OPT_NUM(_T("variance-boost-strength"), variance_boost_strength);
    OPT_NUM(_T("variance-octile"), variance_octile);
    return 1;
#undef OPT_NUM
#undef IS_OPTION
}

int set_cmd(CONF_ENC *cx, const TCHAR *cmd, const bool ignore_parse_err) {
    auto args = sep_cmd(cmd);
    for (int i = 0; i < (int)args.size(); i++) {
        const TCHAR *option_name = nullptr;
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

CONF_ENC get_default_prm() {
    CONF_ENC prm;
    memset(&prm, 0, sizeof(prm));
    set_cmd(&prm, ex_stg->s_enc.default_cmd, true);
    return prm;
}

int parse_cmd(CONF_ENC *cx, const TCHAR *cmd, const bool ignore_parse_err) {
    *cx = get_default_prm();
    return set_cmd(cx, cmd, ignore_parse_err);
}

tstring gen_cmd(const CONF_ENC *cx, bool save_disabled_prm) {
    std::basic_stringstream<TCHAR> cmd;
    CONF_ENC encPrmDefault = get_default_prm();
#define OPT_NUM(str, opt) if ((cx->opt) != (encPrmDefault.opt)) cmd << " --" << (str) << " " << (int)(cx->opt);

    OPT_NUM(_T("preset"), preset);
    OPT_NUM(_T("input-depth"), bit_depth);
    if (cx->rc == get_cx_value(list_rc, L"CRF")) {
        const double rounded = (int)((double)cx->qp / 0.25 + 0.5) * 0.25;
        cmd << " --crf " << std::setprecision(2) << rounded;
        if (save_disabled_prm) {
            OPT_NUM(_T("tbr"), bitrate);
        }
    } else {
        OPT_NUM(_T("rc"), rc);
        if (cx->rc == get_cx_value(list_rc, L"CQP") || save_disabled_prm) {
            cmd << " -q " << (int)(cx->qp + 0.5);
        }
        if (cx->rc == get_cx_value(list_rc, L"VBR") || save_disabled_prm) {
            OPT_NUM("tbr", bitrate);
        }
    }
    OPT_NUM(_T("color-format"), output_csp);
    OPT_NUM(_T("profile"), profile);
    OPT_NUM(_T("pass"), pass);
    OPT_NUM(_T("lp"), lp);

    if (cx->rc == get_cx_value(list_rc, L"CQP")) {
        cmd << " --aq-mode " << 0;
    } else if (cx->rc == get_cx_value(list_rc, L"CRF")) {
        if (cx->aq != 0) OPT_NUM(_T("aq-mode"), aq);
    } else {
        OPT_NUM(_T("aq-mode"), aq);
    }
    OPT_NUM(_T("color-primaries"), color_primaries);
    OPT_NUM(_T("color-range"), color_range);
    OPT_NUM(_T("enable-cdef"), enable_cdef);
    OPT_NUM(_T("enable-dlf"), enable_dlf);
    OPT_NUM(_T("enable-hdr"), enable_hdr);
    OPT_NUM(_T("enable-mfmv"), enable_mfmv);
    OPT_NUM(_T("enable-overlays"), enable_overlays);
    OPT_NUM(_T("enable-restoration"), enable_restoration);
    OPT_NUM(_T("enable-stat-report"), enable_stat_report);
    OPT_NUM(_T("enable-tf"), enable_tf);
    OPT_NUM(_T("enable-tpl-la"), enable_tpl_la);
    OPT_NUM(_T("fast-decode"), fast_decode);
    OPT_NUM(_T("film-grain"), film_grain);
    OPT_NUM(_T("hierarchical-levels"), hierarchical_levels);
    OPT_NUM(_T("irefresh-type"), intra_refresh_type);
    OPT_NUM(_T("keyint"), keyint);
    OPT_NUM(_T("lookahead"), lookahead);
    OPT_NUM(_T("luminance-qp-bias"), luminance_qp_bias);
    OPT_NUM(_T("matrix-coefficients"), matrix_coefficients);
    OPT_NUM(_T("max-qp"), max_qp);
    OPT_NUM(_T("maxsection-pct"), maxsection_pct);
    OPT_NUM(_T("min-qp"), min_qp);
    OPT_NUM(_T("minsection-pct"), minsection_pct);
    OPT_NUM(_T("overshoot-pct"), overshoot_pct);
    OPT_NUM(_T("sharpness"), sharpness);
    OPT_NUM(_T("scd"), scd);
    OPT_NUM(_T("scm"), scm);
    OPT_NUM(_T("tf-strength"), tf_strength);
    OPT_NUM(_T("tile-rows"), tile_rows);
    OPT_NUM(_T("tile-columns"), tile_columns);
    OPT_NUM(_T("transfer-characteristics"), transfer_characteristics);
    OPT_NUM(_T("tune"), tune);
    OPT_NUM(_T("undershoot-pct"), undershoot_pct);
    OPT_NUM(_T("enable-variance-boost"), enable_variance_boost);
    if (cx->enable_variance_boost) {
        OPT_NUM(_T("variance-boost-strength"), variance_boost_strength);
    }
    OPT_NUM(_T("variance-octile"), variance_octile);

    return cmd.str();
}

void set_auto_colormatrix(CONF_ENC *cx, int height) {
    if (cx->matrix_coefficients == COLOR_MATRIX_AUTO)
        cx->matrix_coefficients = (height >= COLOR_MATRIX_THRESHOLD) ? get_cx_value(list_colormatrix, L"bt709") : get_cx_value(list_colormatrix, L"bt601");
    if (cx->color_primaries == COLOR_MATRIX_AUTO)
        cx->color_primaries = (height >= COLOR_MATRIX_THRESHOLD) ? get_cx_value(list_colorprim, L"bt709") : get_cx_value(list_colormatrix, L"bt601");
    if (cx->transfer_characteristics == COLOR_MATRIX_AUTO)
        cx->transfer_characteristics = (height >= COLOR_MATRIX_THRESHOLD) ? get_cx_value(list_transfer, L"bt709") : get_cx_value(list_colormatrix, L"bt601");
}