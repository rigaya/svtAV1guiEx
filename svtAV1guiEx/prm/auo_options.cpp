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

unsigned int wstring_to_string(const wchar_t *wstr, std::string &str, uint32_t codepage) {
    if (wstr == nullptr) {
        str = "";
        return 0;
    }
    uint32_t flags = (codepage == CP_UTF8) ? 0 : WC_NO_BEST_FIT_CHARS;
    int multibyte_length = WideCharToMultiByte(codepage, flags, wstr, -1, nullptr, 0, nullptr, nullptr);
    std::vector<char> tmp(multibyte_length, 0);
    if (0 == WideCharToMultiByte(codepage, flags, wstr, -1, tmp.data(), (int)tmp.size(), nullptr, nullptr)) {
        str.clear();
        return 0;
    }
    str = tmp.data();
    return multibyte_length;
}

std::string wstring_to_string(const std::wstring &wstr, uint32_t codepage = CP_THREAD_ACP) {
    std::string str;
    wstring_to_string(wstr.c_str(), str, codepage);
    return str;
}

unsigned int char_to_wstring(std::wstring &wstr, const char *str, uint32_t codepage) {
    if (str == nullptr) {
        wstr = L"";
        return 0;
    }
    int widechar_length = MultiByteToWideChar(codepage, 0, str, -1, nullptr, 0);
    std::vector<wchar_t> tmp(widechar_length, 0);
    if (0 == MultiByteToWideChar(codepage, 0, str, -1, tmp.data(), (int)tmp.size())) {
        wstr.clear();
        return 0;
    }
    wstr = tmp.data();
    return widechar_length;
}

std::wstring char_to_wstring(const std::string &str, uint32_t codepage = CP_THREAD_ACP) {
    std::wstring wstr;
    char_to_wstring(wstr, str.c_str(), codepage);
    return wstr;
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
    OPT_NUM("rc", rc);
    OPT_NUM("q", qp);
    OPT_NUM("color-format", output_csp);
    OPT_NUM("profile", profile);
    OPT_NUM("pass", pass);
    OPT_NUM("tbr", bitrate);
    OPT_NUM("lp", lp);

    OPT_NUM("adaptive-quantization", aq);
    OPT_NUM("altref-strength", altref_strength);
    OPT_NUM("altref-nframes", altref_nframe);
    OPT_NUM("bias-pct", bias_pct);
    OPT_NUM("bipred-3x3", bipred_3x3);
    OPT_NUM("compound", compound);
    OPT_NUM("cdef-level", cdef_level);
    OPT_NUM("chroma-mode", chroma_mode);
    OPT_NUM("disable-cfl", disable_cfl);
    OPT_NUM("enable-framend-cdf-upd-mode", enable_framend_cdf_upd_mode);
    OPT_NUM("enable-filter-intra", enable_filter_intra);
    OPT_NUM("enable-global-motion", enable_global_motion);
    OPT_NUM("enable-hdr", enable_hdr);
    OPT_NUM("enable-intra-angle-delta", enable_intra_angle_delta);
    OPT_NUM("enable-intra-edge-filter", enable_intra_edge_filter);
    OPT_NUM("enable-intra-edge-skp", enable_intra_edge_skp);
    OPT_NUM("enable-interintra-comp", enable_interintra_comp);
    OPT_NUM("enable-local-warp", enable_local_warp);
    OPT_NUM("enable-mfmv", enable_mfmv);
    OPT_NUM("enable-new-nrst-near-comb", enable_new_nrst_near_comb);
    OPT_NUM("enable-over-bndry-blk", enable_over_bndry_blk);
    OPT_NUM("enable-paeth", enable_paeth);
    OPT_NUM("enable-redundant-blk", enable_redundant_blk);
    OPT_NUM("enable-restoration-filtering", enable_restoration_filtering);
    OPT_NUM("enable-smooth", enable_smooth);
    OPT_NUM("enable-spatial-sse-full-loop-level", enable_spatial_sse_fl);
    OPT_NUM("enable-stat-report", enable_stat_report);
    OPT_NUM("ext-block", ext_block);
    OPT_NUM("hbd-md", hbd_md);
    OPT_NUM("hierarchical-levels", hierarchical_levels);
    OPT_NUM("intrabc-mode", intra_bc_mode);
    OPT_NUM("irefresh-type", intra_refresh_type);
    OPT_NUM("keyint", keyint);
    OPT_NUM("lookahead", lookahead);
    OPT_NUM("max-qp", max_qp);
    OPT_NUM("maxsection-pct", maxsection_pct);
    OPT_NUM("min-qp", min_qp);
    OPT_NUM("minsection-pct", minsection_pct);
    OPT_NUM("mrp-level", mrp_level);
    OPT_NUM("obmc-level", obmc_level);
    OPT_NUM("overshoot-pct", overshoot_pct);
    OPT_NUM("palette-level", palette);
    OPT_NUM("pred-me", pred_me);
    OPT_NUM("rdoq-level", rdoq);
    OPT_NUM("scm", scm);
    OPT_NUM("search-w", search_w);
    OPT_NUM("search-h", search_h);
    OPT_NUM("sg-filter-mode", sg_filter_mode);
    OPT_NUM("sqw", sqw);
    OPT_NUM("subpel", subpel);
    OPT_NUM("tf-level", tf_level);
    OPT_NUM("tile-rows", tile_rows);
    OPT_NUM("tile-columns", tile_columns);
    OPT_NUM("umv", umv);
    OPT_NUM("undershoot-pct", undershoot_pct);
    OPT_NUM("use-default-me-hme", use_default_me_hme);
    OPT_NUM("vbv-bufsize", vbv_bufsize);
    OPT_NUM("wn-filter-mode", wn_filter_mode);
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
    OPT_NUM("rc", rc);
    if ((cx->qp) != (encPrmDefault.qp)) cmd << " -q " << (int)(cx->qp);
    OPT_NUM("color-format", output_csp);
    OPT_NUM("profile", profile);
    OPT_NUM("pass", pass);
    OPT_NUM("tbr", bitrate);
    OPT_NUM("lp", lp);

    OPT_NUM("adaptive-quantization", aq);
    OPT_NUM("altref-strength", altref_strength);
    OPT_NUM("altref-nframes", altref_nframe);
    OPT_NUM("bias-pct", bias_pct);
    OPT_NUM("bipred-3x3", bipred_3x3);
    OPT_NUM("compound", compound);
    OPT_NUM("cdef-level", cdef_level);
    OPT_NUM("chroma-mode", chroma_mode);
    OPT_NUM("disable-cfl", disable_cfl);
    OPT_NUM("enable-framend-cdf-upd-mode", enable_framend_cdf_upd_mode);
    OPT_NUM("enable-filter-intra", enable_filter_intra);
    OPT_NUM("enable-global-motion", enable_global_motion);
    OPT_NUM("enable-hdr", enable_hdr);
    OPT_NUM("enable-intra-angle-delta", enable_intra_angle_delta);
    OPT_NUM("enable-intra-edge-filter", enable_intra_edge_filter);
    OPT_NUM("enable-intra-edge-skp", enable_intra_edge_skp);
    OPT_NUM("enable-interintra-comp", enable_interintra_comp);
    OPT_NUM("enable-local-warp", enable_local_warp);
    OPT_NUM("enable-mfmv", enable_mfmv);
    OPT_NUM("enable-new-nrst-near-comb", enable_new_nrst_near_comb);
    OPT_NUM("enable-over-bndry-blk", enable_over_bndry_blk);
    OPT_NUM("enable-paeth", enable_paeth);
    OPT_NUM("enable-redundant-blk", enable_redundant_blk);
    OPT_NUM("enable-restoration-filtering", enable_restoration_filtering);
    OPT_NUM("enable-smooth", enable_smooth);
    OPT_NUM("enable-spatial-sse-full-loop-level", enable_spatial_sse_fl);
    OPT_NUM("enable-stat-report", enable_stat_report);
    OPT_NUM("ext-block", ext_block);
    OPT_NUM("hbd-md", hbd_md);
    OPT_NUM("hierarchical-levels", hierarchical_levels);
    OPT_NUM("intrabc-mode", intra_bc_mode);
    OPT_NUM("irefresh-type", intra_refresh_type);
    OPT_NUM("keyint", keyint);
    OPT_NUM("lookahead", lookahead);
    OPT_NUM("max-qp", max_qp);
    OPT_NUM("maxsection-pct", maxsection_pct);
    OPT_NUM("min-qp", min_qp);
    OPT_NUM("minsection-pct", minsection_pct);
    OPT_NUM("mrp-level", mrp_level);
    OPT_NUM("overshoot-pct", overshoot_pct);
    OPT_NUM("obmc-level", obmc_level);
    OPT_NUM("palette-level", palette);
    OPT_NUM("pred-me", pred_me);
    OPT_NUM("rdoq-level", rdoq);
    OPT_NUM("scm", scm);
    OPT_NUM("search-w", search_w);
    OPT_NUM("search-h", search_h);
    OPT_NUM("sg-filter-mode", sg_filter_mode);
    OPT_NUM("sqw", sqw);
    OPT_NUM("subpel", subpel);
    OPT_NUM("tf-level", tf_level);
    OPT_NUM("tile-rows", tile_rows);
    OPT_NUM("tile-columns", tile_columns);
    OPT_NUM("umv", umv);
    OPT_NUM("undershoot-pct", undershoot_pct);
    OPT_NUM("use-default-me-hme", use_default_me_hme);
    OPT_NUM("vbv-bufsize", vbv_bufsize);
    OPT_NUM("wn-filter-mode", wn_filter_mode);

    return cmd.str();
}
