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
    if (IS_OPTION("enc-mode")) {
        i++;
        return to_int(&cx->enc_mode, argv[i]);
    }
    if (IS_OPTION("bit-depth")) {
        i++;
        return to_int(&cx->bit_depth, argv[i]);
    }
    if (IS_OPTION("q")) {
        i++;
        return to_int(&cx->qp, argv[i]);
    }
    if (IS_OPTION("tbr")) {
        i++;
        return to_int(&cx->bitrate, argv[i]);
    }
    if (IS_OPTION("rc")) {
        i++;
        return to_int(&cx->rc, argv[i]);
    }
    if (IS_OPTION("hierarchical-levels")) {
        i++;
        return to_int(&cx->hierarchical_levels, argv[i]);
    }
    if (IS_OPTION("intra-period")) {
        i++;
        return to_int(&cx->intra_period, argv[i]);
    }
    if (IS_OPTION("irefresh-type")) {
        i++;
        return to_int(&cx->intra_refresh_type, argv[i]);
    }
    if (IS_OPTION("use-default-me-hme")) {
        i++;
        return to_int(&cx->use_default_me_hme, argv[i]);
    }
    if (IS_OPTION("in-loop-me")) {
        i++;
        return to_int(&cx->in_loop_me, argv[i]);
    }
    if (IS_OPTION("local-warp")) {
        i++;
        return to_int(&cx->local_warp, argv[i]);
    }
    if (IS_OPTION("ext-block")) {
        i++;
        return to_int(&cx->ext_block, argv[i]);
    }
    if (IS_OPTION("scm")) {
        i++;
        return to_int(&cx->scm, argv[i]);
    }
    if (IS_OPTION("adaptive-quantization")) {
        i++;
        return to_int(&cx->aq, argv[i]);
    }
    if (IS_OPTION("search-w")) {
        i++;
        return to_int(&cx->search_w, argv[i]);
    }
    if (IS_OPTION("search-h")) {
        i++;
        return to_int(&cx->search_h, argv[i]);
    }
    if (IS_OPTION("lad")) {
        i++;
        return to_int(&cx->lad, argv[i]);
    }
    if (IS_OPTION("scd")) {
        i++;
        return to_int(&cx->scd, argv[i]);
    }
    if (IS_OPTION("lp")) {
        i++;
        return to_int(&cx->lp, argv[i]);
    }
    if (IS_OPTION("tile-rows")) {
        i++;
        return to_int(&cx->tile_rows, argv[i]);
    }
    if (IS_OPTION("tile-columns")) {
        i++;
        return to_int(&cx->tile_columns, argv[i]);
    }
    if (IS_OPTION("rdoq")) {
        i++;
        return to_int(&cx->rdoq, argv[i]);
    }
    if (IS_OPTION("pred-me")) {
        i++;
        return to_int(&cx->pred_me, argv[i]);
    }
    if (IS_OPTION("restoration-filtering")) {
        i++;
        return to_int(&cx->restoration_filtering, argv[i]);
    }
    if (IS_OPTION("framend-cdf-upd-mode")) {
        i++;
        return to_int(&cx->framend_cdf_upd_mode, argv[i]);
    }
    if (IS_OPTION("class-12")) {
        i++;
        return to_int(&cx->class_12, argv[i]);
    }
    if (IS_OPTION("intra-edge-skp")) {
        i++;
        return to_int(&cx->intra_edge_skp, argv[i]);
    }
    if (IS_OPTION("interintra-comp")) {
        i++;
        return to_int(&cx->interintra_comp, argv[i]);
    }
    if (IS_OPTION("frac-search-64")) {
        i++;
        return to_int(&cx->frac_search_64, argv[i]);
    }
    if (IS_OPTION("mfmv")) {
        i++;
        return to_int(&cx->mfmv, argv[i]);
    }
    if (IS_OPTION("trellis")) {
        i++;
        return to_int(&cx->trellis, argv[i]);
    }
    if (IS_OPTION("redundant-blk")) {
        i++;
        return to_int(&cx->redundant_blk, argv[i]);
    }
    if (IS_OPTION("spatial-sse-fl")) {
        i++;
        return to_int(&cx->spatial_sse_fl, argv[i]);
    }
    if (IS_OPTION("subpel")) {
        i++;
        return to_int(&cx->subpel, argv[i]);
    }
    if (IS_OPTION("over-bndry-blk")) {
        i++;
        return to_int(&cx->over_bndry_blk, argv[i]);
    }
    if (IS_OPTION("-new-nrst-near-comb")) {
        i++;
        return to_int(&cx->new_nrst_near_comb, argv[i]);
    }
    if (IS_OPTION("nx4-4xn-mv-inject")) {
        i++;
        return to_int(&cx->nx4_4xn_mv_inject, argv[i]);
    }
    if (IS_OPTION("prune-unipred-me")) {
        i++;
        return to_int(&cx->prune_unipred_me, argv[i]);
    }
    if (IS_OPTION("prune-ref-rec-part")) {
        i++;
        return to_int(&cx->prune_ref_rec_part, argv[i]);
    }
    if (IS_OPTION("bipred-3x3")) {
        i++;
        return to_int(&cx->bipred_3x3, argv[i]);
    }
    if (IS_OPTION("compound")) {
        i++;
        return to_int(&cx->compound, argv[i]);
    }
    if (IS_OPTION("palette")) {
        i++;
        return to_int(&cx->palette, argv[i]);
    }
    if (IS_OPTION("olpd-refinement")) {
        i++;
        return to_int(&cx->olpd_refinement, argv[i]);
    }
    if (IS_OPTION("umv")) {
        i++;
        return to_int(&cx->umv, argv[i]);
    }
    if (IS_OPTION("sqw")) {
        i++;
        return to_int(&cx->sqw, argv[i]);
    }
    return 1;
#undef IS_OPTION
}

int set_cmd(CONF_ENCODER *cx, const char *cmd, const bool ignore_parse_err) {
    auto args = sep_cmd(cmd);
    for (int i = 0; i < args.size(); i++) {
        const char *option_name = nullptr;
        if (args[i][0] == '|') {
            break;
        } else if (args[i][0] == '-') {
            option_name = &args[i][1];
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
#define OPT_NUM(str, opt) if ((cx->opt) != (encPrmDefault.opt)) cmd << " " << (str) << " " << (int)(cx->opt);

    OPT_NUM("-enc-mode", enc_mode);
    OPT_NUM("-bit-depth", bit_depth);
    OPT_NUM("-rc", rc);
    OPT_NUM("-q", qp);
    OPT_NUM("-tbr", bitrate);
    OPT_NUM("-hierarchical-levels", hierarchical_levels);
    OPT_NUM("-intra-period", intra_period);
    OPT_NUM("-irefresh-type", intra_refresh_type);
    OPT_NUM("-use-default-me-hme", use_default_me_hme);
    OPT_NUM("-in-loop-me", in_loop_me);
    OPT_NUM("-local-warp", local_warp);
    OPT_NUM("-ext-block", ext_block);
    OPT_NUM("-scm", scm);
    OPT_NUM("-adaptive-quantization", aq);
    OPT_NUM("-search-w", search_w);
    OPT_NUM("-search-h", search_h);
    OPT_NUM("-lad", lad);
    OPT_NUM("-scd", scd);
    OPT_NUM("-lp", lp);
    OPT_NUM("-tile-rows", tile_rows);
    OPT_NUM("-tile-columns", tile_columns);

    OPT_NUM("-pred-me", pred_me);
    OPT_NUM("-rdoq", rdoq);
    OPT_NUM("-restoration-filtering", restoration_filtering);
    OPT_NUM("-framend-cdf-upd-mode", framend_cdf_upd_mode);
    OPT_NUM("-class-12", class_12);
    OPT_NUM("-intra-edge-skp", intra_edge_skp);
    OPT_NUM("-interintra-comp", interintra_comp);
    OPT_NUM("-frac-search-64", frac_search_64);
    OPT_NUM("-mfmv", mfmv);
    OPT_NUM("-redundant-blk", redundant_blk);
    OPT_NUM("-spatial-sse-fl", spatial_sse_fl);
    OPT_NUM("-subpel", subpel);
    OPT_NUM("-over-bndry-blk", over_bndry_blk);
    OPT_NUM("-new-nrst-near-comb", new_nrst_near_comb);
    OPT_NUM("-nx4-4xn-mv-inject", nx4_4xn_mv_inject);
    OPT_NUM("-prune-unipred-me", prune_unipred_me);
    OPT_NUM("-prune-ref-rec-part", prune_ref_rec_part);
    OPT_NUM("-bipred_3x3", bipred_3x3);
    OPT_NUM("-compound", compound);
    OPT_NUM("-palette", palette);
    OPT_NUM("-olpd-refinement", olpd_refinement);
    OPT_NUM("-umv", umv);
    OPT_NUM("-sqw", sqw);

    return cmd.str();
}
