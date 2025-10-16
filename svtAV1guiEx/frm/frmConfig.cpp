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

//以下warning C4100を黙らせる
//C4100 : 引数は関数の本体部で 1 度も参照されません。
#pragma warning( push )
#pragma warning( disable: 4100 )

#include "auo_version.h"
#include "auo_frm.h"
#include "auo_faw2aac.h"
#include "frmConfig.h"
#include "frmSaveNewStg.h"
#include "frmOtherSettings.h"
#include "frmBitrateCalculator.h"

using namespace svtAV1guiEx;

/// -------------------------------------------------
///     設定画面の表示
/// -------------------------------------------------
[STAThreadAttribute]
void ShowfrmConfig(CONF_GUIEX *conf, const SYSTEM_DATA *sys_dat) {
    if (!sys_dat->exstg->s_local.disable_visual_styles)
        System::Windows::Forms::Application::EnableVisualStyles();
    System::IO::Directory::SetCurrentDirectory(String(sys_dat->aviutl_dir).ToString());
    frmConfig frmConf(conf, sys_dat);
    frmConf.ShowDialog();
}

/// -------------------------------------------------
///     frmSaveNewStg 関数
/// -------------------------------------------------
System::Boolean frmSaveNewStg::checkStgFileName(String^ stgName) {
    String^ fileName;
    if (stgName->Length == 0)
        return false;

    if (!ValidiateFileName(stgName)) {
        MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_INVALID_CHAR), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
    if (String::Compare(Path::GetExtension(stgName), L".stg", true))
        stgName += L".stg";
    if (File::Exists(fileName = Path::Combine(fsnCXFolderBrowser->GetSelectedFolder(), stgName)))
        if (MessageBox::Show(stgName + LOAD_CLI_STRING(AUO_CONFIG_ALREADY_EXISTS), LOAD_CLI_STRING(AUO_CONFIG_OVERWRITE_CHECK), MessageBoxButtons::YesNo, MessageBoxIcon::Question)
            != System::Windows::Forms::DialogResult::Yes)
            return false;
    StgFileName = fileName;
    return true;
}

System::Void frmSaveNewStg::setStgDir(String^ _stgDir) {
    StgDir = _stgDir;
    fsnCXFolderBrowser->SetRootDirAndReload(StgDir);
}


/// -------------------------------------------------
///     frmBitrateCalculator 関数
/// -------------------------------------------------
System::Void frmBitrateCalculator::Init(int VideoBitrate, int AudioBitrate, bool BTVBEnable, bool BTABEnable, int ab_max, const AuoTheme themeTo, const DarkenWindowStgReader *dwStg) {
    guiEx_settings exStg(true);
    exStg.load_fbc();
    enable_events = false;
    dwStgReader = dwStg;
    CheckTheme(themeTo);
    fbcTXSize->Text = exStg.s_fbc.initial_size.ToString("F2");
    fbcChangeTimeSetMode(exStg.s_fbc.calc_time_from_frame != 0);
    fbcRBCalcRate->Checked = exStg.s_fbc.calc_bitrate != 0;
    fbcRBCalcSize->Checked = !fbcRBCalcRate->Checked;
    fbcTXMovieFrameRate->Text = Convert::ToString(exStg.s_fbc.last_fps);
    fbcNUMovieFrames->Value = exStg.s_fbc.last_frame_num;
    fbcNULengthHour->Value = Convert::ToDecimal((int)exStg.s_fbc.last_time_in_sec / 3600);
    fbcNULengthMin->Value = Convert::ToDecimal((int)(exStg.s_fbc.last_time_in_sec % 3600) / 60);
    fbcNULengthSec->Value =  Convert::ToDecimal((int)exStg.s_fbc.last_time_in_sec % 60);
    SetBTVBEnabled(BTVBEnable);
    SetBTABEnabled(BTABEnable, ab_max);
    SetNUVideoBitrate(VideoBitrate);
    SetNUAudioBitrate(AudioBitrate);
    enable_events = true;
}
System::Void frmBitrateCalculator::CheckTheme(const AuoTheme themeTo) {
    //変更の必要がなければ終了
    if (themeTo == themeMode) return;
    if (dwStgReader == nullptr) return;

    //一度ウィンドウの再描画を完全に抑止する
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 0, 0);
    SetAllColor(this, themeTo, this->GetType(), dwStgReader);
    SetAllMouseMove(this, themeTo);
    //一度ウィンドウの再描画を再開し、強制的に再描画させる
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 1, 0);
    this->Refresh();
    themeMode = themeTo;
}
System::Void frmBitrateCalculator::frmBitrateCalculator_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
    guiEx_settings exStg(true);
    exStg.load_fbc();
    exStg.s_fbc.calc_bitrate = fbcRBCalcRate->Checked;
    exStg.s_fbc.calc_time_from_frame = fbcPNMovieFrames->Visible;
    exStg.s_fbc.last_fps = Convert::ToDouble(fbcTXMovieFrameRate->Text);
    exStg.s_fbc.last_frame_num = Convert::ToInt32(fbcNUMovieFrames->Value);
    exStg.s_fbc.last_time_in_sec = Convert::ToInt32(fbcNULengthHour->Value) * 3600
                                 + Convert::ToInt32(fbcNULengthMin->Value) * 60
                                 + Convert::ToInt32(fbcNULengthSec->Value);
    if (fbcRBCalcRate->Checked)
        exStg.s_fbc.initial_size = Convert::ToDouble(fbcTXSize->Text);
    exStg.save_fbc();
    frmConfig^ fcg = dynamic_cast<frmConfig^>(this->Owner);
    if (fcg != nullptr)
        fcg->InformfbcClosed();
}
System::Void frmBitrateCalculator::fbcRBCalcRate_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    if (fbcRBCalcRate->Checked && Convert::ToDouble(fbcTXSize->Text) <= 0.0) {
        guiEx_settings exStg(true);
        exStg.load_fbc();
        fbcTXSize->Text = exStg.s_fbc.initial_size.ToString("F2");
    }
}
System::Void frmBitrateCalculator::fbcBTVBApply_Click(System::Object^  sender, System::EventArgs^  e) {
    frmConfig^ fcg = dynamic_cast<frmConfig^>(this->Owner);
    if (fcg != nullptr)
        fcg->SetVideoBitrate((int)fbcNUBitrateVideo->Value);
}
System::Void frmBitrateCalculator::fbcBTABApply_Click(System::Object^  sender, System::EventArgs^  e) {
    frmConfig^ fcg = dynamic_cast<frmConfig^>(this->Owner);
    if (fcg != nullptr)
        fcg->SetAudioBitrate((int)fbcNUBitrateAudio->Value);
}
System::Void frmBitrateCalculator::fbcMouseEnter_SetColor(System::Object^  sender, System::EventArgs^  e) {
    fcgMouseEnterLeave_SetColor(sender, themeMode, DarkenWindowState::Hot, dwStgReader);
}
System::Void frmBitrateCalculator::fbcMouseLeave_SetColor(System::Object^  sender, System::EventArgs^  e) {
    fcgMouseEnterLeave_SetColor(sender, themeMode, DarkenWindowState::Normal, dwStgReader);
}
System::Void frmBitrateCalculator::SetAllMouseMove(Control ^top, const AuoTheme themeTo) {
    if (themeTo == themeMode) return;
    System::Type^ type = top->GetType();
    if (type == CheckBox::typeid) {
        top->MouseEnter += gcnew System::EventHandler(this, &frmBitrateCalculator::fbcMouseEnter_SetColor);
        top->MouseLeave += gcnew System::EventHandler(this, &frmBitrateCalculator::fbcMouseLeave_SetColor);
    }
    for (int i = 0; i < top->Controls->Count; i++) {
        SetAllMouseMove(top->Controls[i], themeTo);
    }
}

/// -------------------------------------------------
///     frmConfig 関数  (frmBitrateCalculator関連)
/// -------------------------------------------------
System::Void frmConfig::CloseBitrateCalc() {
    frmBitrateCalculator::Instance::get()->Close();
}
System::Void frmConfig::fcgTSBBitrateCalc_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    if (fcgTSBBitrateCalc->Checked) {
        int videoBitrate = (int)fcgNUBitrate->Value;
        bool videoBitrateMode = (x264_encmode_to_RCint[fcgCXRC->SelectedIndex] == ENC_RC_BITRATE);

        frmBitrateCalculator::Instance::get()->Init(
            (videoBitrateMode) ? videoBitrate : 0,
            (fcgNUAudioBitrate->Visible) ? (int)fcgNUAudioBitrate->Value : 0,
            videoBitrateMode,
            fcgNUAudioBitrate->Visible,
            (int)fcgNUAudioBitrate->Maximum,
            themeMode,
            dwStgReader
            );
        frmBitrateCalculator::Instance::get()->Owner = this;
        frmBitrateCalculator::Instance::get()->Show();
    } else {
        frmBitrateCalculator::Instance::get()->Close();
    }
}
System::Void frmConfig::SetfbcBTABEnable(bool enable, int max) {
    frmBitrateCalculator::Instance::get()->SetBTABEnabled(fcgNUAudioBitrate->Visible, max);
}
System::Void frmConfig::SetfbcBTVBEnable(bool enable) {
    frmBitrateCalculator::Instance::get()->SetBTVBEnabled(enable);
}

System::Void frmConfig::SetVideoBitrate(int bitrate) {
    if (x264_encmode_to_RCint[fcgCXRC->SelectedIndex] == ENC_RC_BITRATE)
        fcgNUBitrate->Value = bitrate;
}

System::Void frmConfig::SetAudioBitrate(int bitrate) {
    SetNUValue(fcgNUAudioBitrate, bitrate);
}
System::Void frmConfig::InformfbcClosed() {
    fcgTSBBitrateCalc->Checked = false;
}

/// -------------------------------------------------
///     frmConfig 関数
/// -------------------------------------------------
/////////////   LocalStg関連  //////////////////////
System::Void frmConfig::LoadLocalStg() {
    guiEx_settings *_ex_stg = sys_dat->exstg;
    _ex_stg->load_encode_stg();
    LocalStg.x264ExeName     = String(_ex_stg->s_enc.filename).ToString();
    LocalStg.x264Path        = String(_ex_stg->s_enc.fullpath).ToString();
    LocalStg.CustomTmpDir    = String(_ex_stg->s_local.custom_tmp_dir).ToString();
    LocalStg.CustomAudTmpDir = String(_ex_stg->s_local.custom_audio_tmp_dir).ToString();
    LocalStg.CustomMP4TmpDir = String(_ex_stg->s_local.custom_mp4box_tmp_dir).ToString();
    LocalStg.LastAppDir      = String(_ex_stg->s_local.app_dir).ToString();
    LocalStg.LastBatDir      = String(_ex_stg->s_local.bat_dir).ToString();
    LocalStg.MP4MuxerExeName = String(_ex_stg->s_mux[MUXER_MP4].filename).ToString();
    LocalStg.MP4MuxerPath    = String(_ex_stg->s_mux[MUXER_MP4].fullpath).ToString();
    LocalStg.MKVMuxerExeName = String(_ex_stg->s_mux[MUXER_MKV].filename).ToString();
    LocalStg.MKVMuxerPath    = String(_ex_stg->s_mux[MUXER_MKV].fullpath).ToString();
    LocalStg.TC2MP4ExeName   = String(_ex_stg->s_mux[MUXER_TC2MP4].filename).ToString();
    LocalStg.TC2MP4Path      = String(_ex_stg->s_mux[MUXER_TC2MP4].fullpath).ToString();
    LocalStg.MP4RawExeName   = String(_ex_stg->s_mux[MUXER_MP4_RAW].filename).ToString();
    LocalStg.MP4RawPath      = String(_ex_stg->s_mux[MUXER_MP4_RAW].fullpath).ToString();

    LocalStg.audEncName->Clear();
    LocalStg.audEncExeName->Clear();
    LocalStg.audEncPath->Clear();
    for (int i = 0; i < _ex_stg->s_aud_ext_count; i++) {
        LocalStg.audEncName->Add(String(_ex_stg->s_aud_ext[i].dispname).ToString());
        LocalStg.audEncExeName->Add(String(_ex_stg->s_aud_ext[i].filename).ToString());
        LocalStg.audEncPath->Add(String(_ex_stg->s_aud_ext[i].fullpath).ToString());
    }
    if (_ex_stg->s_local.large_cmdbox)
        fcgTXCmd_DoubleClick(nullptr, nullptr); //初期状態は縮小なので、拡大
}

System::Boolean frmConfig::CheckLocalStg() {
    bool error = false;
    String^ err = "";
    //x264のチェック
    if (LocalStg.x264Path->Length > 0
        && !File::Exists(LocalStg.x264Path)) {
        error = true;
        err += LOAD_CLI_STRING(AUO_CONFIG_VID_ENC_NOT_EXIST) + L"\n [ " + LocalStg.x264Path + L" ]\n";
    }
    //音声エンコーダのチェック (実行ファイル名がない場合はチェックしない)
    if (useAudioExt()
        && LocalStg.audEncExeName[fcgCXAudioEncoder->SelectedIndex]->Length) {
        String^ AudioEncoderPath = LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex];
        if (AudioEncoderPath->Length > 0
            && !File::Exists(AudioEncoderPath)
            && (fcgCXAudioEncoder->SelectedIndex != sys_dat->exstg->get_faw_index(!useAudioExt())) ) {
            //音声実行ファイルがない かつ
            //選択された音声がfawでない または fawであってもfaw2aacがない
            if (error) err += L"\n\n";
            error = true;
            err += LOAD_CLI_STRING(AUO_CONFIG_AUD_ENC_NOT_EXIST) + L"\n [ " + AudioEncoderPath + L" ]\n";
        }
    }
    //FAWのチェック
    if (fcgCBFAWCheck->Checked) {
        if (sys_dat->exstg->get_faw_index(!useAudioExt()) == FAW_INDEX_ERROR) {
            if (error) err += L"\n\n";
            error = true;
            err += LOAD_CLI_STRING(AUO_CONFIG_FAW_STG_NOT_FOUND_IN_INI1) + L"\n"
                +  LOAD_CLI_STRING(AUO_CONFIG_FAW_STG_NOT_FOUND_IN_INI2) + L"\n"
                +  LOAD_CLI_STRING(AUO_CONFIG_FAW_STG_NOT_FOUND_IN_INI3);
        }
    }
    //自動マルチパスの自動ビットレート設定のチェック
    if (fcgLBAMPAutoBitrate != nullptr && fcgLBAMPAutoBitrate->Visible) {
        if (error) err += L"\n\n";
        error = true;
        err += LOAD_CLI_STRING(AUO_CONFIG_AMP_STG_INVALID1) + L"\n"
            +  LOAD_CLI_STRING(AUO_CONFIG_AMP_STG_INVALID2) + L"\n"
            +  LOAD_CLI_STRING(AUO_CONFIG_AMP_STG_INVALID3) + L"\n"
            +  LOAD_CLI_STRING(AUO_CONFIG_AMP_STG_INVALID4);
    }
    if (error)
        MessageBox::Show(this, err, LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
    return error;
}

System::Void frmConfig::SaveLocalStg() {
    guiEx_settings *_ex_stg = sys_dat->exstg;
    _ex_stg->load_encode_stg();
    _ex_stg->s_local.large_cmdbox = fcgTXCmd->Multiline;
    GetWCHARfromString(_ex_stg->s_enc.fullpath,                _countof(_ex_stg->s_enc.fullpath),               LocalStg.x264Path);
    GetWCHARfromString(_ex_stg->s_local.custom_tmp_dir,        _countof(_ex_stg->s_local.custom_tmp_dir),        LocalStg.CustomTmpDir);
    GetWCHARfromString(_ex_stg->s_local.custom_mp4box_tmp_dir, _countof(_ex_stg->s_local.custom_mp4box_tmp_dir), LocalStg.CustomMP4TmpDir);
    GetWCHARfromString(_ex_stg->s_local.custom_audio_tmp_dir,  _countof(_ex_stg->s_local.custom_audio_tmp_dir),  LocalStg.CustomAudTmpDir);
    GetWCHARfromString(_ex_stg->s_local.app_dir,               _countof(_ex_stg->s_local.app_dir),               LocalStg.LastAppDir);
    GetWCHARfromString(_ex_stg->s_local.bat_dir,               _countof(_ex_stg->s_local.bat_dir),               LocalStg.LastBatDir);
    GetWCHARfromString(_ex_stg->s_mux[MUXER_MP4].fullpath,     _countof(_ex_stg->s_mux[MUXER_MP4].fullpath),     LocalStg.MP4MuxerPath);
    GetWCHARfromString(_ex_stg->s_mux[MUXER_MKV].fullpath,     _countof(_ex_stg->s_mux[MUXER_MKV].fullpath),     LocalStg.MKVMuxerPath);
    GetWCHARfromString(_ex_stg->s_mux[MUXER_TC2MP4].fullpath,  _countof(_ex_stg->s_mux[MUXER_TC2MP4].fullpath),  LocalStg.TC2MP4Path);
    GetWCHARfromString(_ex_stg->s_mux[MUXER_MP4_RAW].fullpath, _countof(_ex_stg->s_mux[MUXER_MP4_RAW].fullpath), LocalStg.MP4RawPath);
    for (int i = 0; i < _ex_stg->s_aud_ext_count; i++)
        GetWCHARfromString(_ex_stg->s_aud_ext[i].fullpath,         _countof(_ex_stg->s_aud_ext[i].fullpath),             LocalStg.audEncPath[i]);
    _ex_stg->save_local();
}

System::Void frmConfig::SetLocalStg() {
    fcgLBX264Path->Text           = System::String(ENCODER_NAME).ToString() + L".exe" + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);
    fcgLBX264PathSub->Text        = System::String(ENCODER_NAME).ToString() + L".exe" + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);
    fcgTXX264Path->Text           = LocalStg.x264Path;
    fcgTXX264PathSub->Text        = LocalStg.x264Path;
    fcgTXMP4MuxerPath->Text       = LocalStg.MP4MuxerPath;
    fcgTXMKVMuxerPath->Text       = LocalStg.MKVMuxerPath;
    fcgTXTC2MP4Path->Text         = LocalStg.TC2MP4Path;
    fcgTXMP4RawPath->Text         = LocalStg.MP4RawPath;
    fcgTXCustomAudioTempDir->Text = LocalStg.CustomAudTmpDir;
    fcgTXCustomTempDir->Text      = LocalStg.CustomTmpDir;
    fcgTXMP4BoxTempDir->Text      = LocalStg.CustomMP4TmpDir;
    fcgLBMP4MuxerPath->Text       = LocalStg.MP4MuxerExeName + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);
    fcgLBMKVMuxerPath->Text       = LocalStg.MKVMuxerExeName + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);
    fcgLBTC2MP4Path->Text         = LocalStg.TC2MP4ExeName   + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);
    fcgLBMP4RawPath->Text         = LocalStg.MP4RawExeName   + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);

    fcgTXX264Path->SelectionStart           = fcgTXX264Path->Text->Length;
    fcgTXX264PathSub->SelectionStart        = fcgTXX264PathSub->Text->Length;
    fcgTXMP4MuxerPath->SelectionStart       = fcgTXMP4MuxerPath->Text->Length;
    fcgTXTC2MP4Path->SelectionStart         = fcgTXTC2MP4Path->Text->Length;
    fcgTXMKVMuxerPath->SelectionStart       = fcgTXMKVMuxerPath->Text->Length;
    fcgTXMP4RawPath->SelectionStart         = fcgTXMP4RawPath->Text->Length;
}


//////////////       その他イベント処理   ////////////////////////
System::Void frmConfig::ActivateToolTip(bool Enable) {
    fcgTTEx->Active = Enable;
    fcgTTX264->Active = Enable;
    fcgTTX264Version->Active = Enable;
}

System::Void frmConfig::fcgTSBOtherSettings_Click(System::Object^  sender, System::EventArgs^  e) {
    frmOtherSettings::Instance::get()->stgDir = String(sys_dat->exstg->s_local.stg_dir).ToString();
    frmOtherSettings::Instance::get()->SetTheme(themeMode, dwStgReader);
    frmOtherSettings::Instance::get()->ShowDialog();
    TCHAR buf[MAX_PATH_LEN];
    GetWCHARfromString(buf, _countof(buf), frmOtherSettings::Instance::get()->stgDir);
    if (_tcscmp(buf, sys_dat->exstg->s_local.stg_dir)) {
        //変更があったら保存する
        _tcscpy_s(sys_dat->exstg->s_local.stg_dir, _countof(sys_dat->exstg->s_local.stg_dir), buf);
        sys_dat->exstg->save_local();
        InitStgFileList();
    }
    //再読み込み
    guiEx_settings stg;
    stg.load_encode_stg();
    log_reload_settings();
    sys_dat->exstg->s_local.default_audenc_use_in = stg.s_local.default_audenc_use_in;
    sys_dat->exstg->s_local.default_audio_encoder_ext = stg.s_local.default_audio_encoder_ext;
    sys_dat->exstg->s_local.default_audio_encoder_in = stg.s_local.default_audio_encoder_in;
    SetStgEscKey(stg.s_local.enable_stg_esc_key != 0);
    ActivateToolTip(stg.s_local.disable_tooltip_help == FALSE);
    if (str_has_char(stg.s_local.conf_font.name))
        SetFontFamilyToForm(this, gcnew FontFamily(String(stg.s_local.conf_font.name).ToString()), this->Font->FontFamily);
}

System::Void frmConfig::fcgTSBCMDOnly_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    //CLIモードとの切り替え
    //一度ウィンドウの再描画を完全に抑止する
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 0, 0);
    //なぜか知らんが、Visibleプロパティをfalseにするだけでは非表示にできない
    //しょうがないので参照の削除と挿入を行う
    if (fcgTSBCMDOnly->Checked) {
        fcgtabControlVideo->TabPages->RemoveAt(1);
        fcgtabControlVideo->TabPages->RemoveAt(0);
        fcgtabPageExSettings->Text = L"映像";
        fcggroupBoxCmdEx->Text = L"コマンドライン";
    } else {
        fcgtabControlVideo->TabPages->Insert(0, fcgtabPageSVTAV1_1);
        fcgtabControlVideo->TabPages->Insert(1, fcgtabPageSVTAV1_2);
        fcgtabPageExSettings->Text = L"拡張";
        fcggroupBoxCmdEx->Text = L"追加コマンド";
    }
    //一度ウィンドウの再描画を再開し、強制的に再描画させる
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 1, 0);
    this->Refresh();

    fcgChangeEnabled(sender, e);
    fcgRebuildCmd(sender, e);
}

System::Void frmConfig::fcgCBAFS_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    fcgCBAFSBitrateCorrection->Enabled = fcgCBAFS->Checked;
    if (fcgCBAFS->Checked) {
        //fcgCBMP4MuxerExt->Checked      = true;
        //fcgCBMKVMuxerExt->Checked      = true;
    }
    //fcgCBMP4MuxerExt->Enabled          = !fcgCBAFS->Checked;
    //fcgCBMKVMuxerExt->Enabled          = !fcgCBAFS->Checked;

    const bool enable_tc2mp4_muxer = (0 != str_has_char(sys_dat->exstg->s_mux[MUXER_TC2MP4].base_cmd));
    if (enable_tc2mp4_muxer) {
        int muxer_cmdex = fcgCXMP4CmdEx->SelectedIndex;
        setMuxerCmdExNames(fcgCXMP4CmdEx, (fcgCBAFS->Checked) ? MUXER_TC2MP4 : MUXER_MP4);
        fcgCXMP4CmdEx->SelectedIndex = muxer_cmdex;
    }
}

System::Boolean frmConfig::EnableSettingsNoteChange(bool Enable) {
    if (fcgTSTSettingsNotes->Visible == Enable &&
        fcgTSLSettingsNotes->Visible == !Enable)
        return true;
    if (CountStringBytes(fcgTSTSettingsNotes->Text) > fcgTSTSettingsNotes->MaxLength - 1) {
        MessageBox::Show(this, LOAD_CLI_STRING(AUO_CONFIG_TEXT_LIMIT_LENGTH), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
        fcgTSTSettingsNotes->Focus();
        fcgTSTSettingsNotes->SelectionStart = fcgTSTSettingsNotes->Text->Length;
        return false;
    }
    fcgTSTSettingsNotes->Visible = Enable;
    fcgTSLSettingsNotes->Visible = !Enable;
    if (Enable) {
        fcgTSTSettingsNotes->Text = fcgTSLSettingsNotes->Text;
        fcgTSTSettingsNotes->Focus();
        bool isDefaultNote = fcgTSLSettingsNotes->Overflow != ToolStripItemOverflow::Never;
        fcgTSTSettingsNotes->Select((isDefaultNote) ? 0 : fcgTSTSettingsNotes->Text->Length, fcgTSTSettingsNotes->Text->Length);
    } else {
        SetfcgTSLSettingsNotes(fcgTSTSettingsNotes->Text);
        CheckOtherChanges(nullptr, nullptr);
    }
    return true;
}


///////////////////  メモ関連  ///////////////////////////////////////////////
System::Void frmConfig::fcgTSLSettingsNotes_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
    EnableSettingsNoteChange(true);
}
System::Void frmConfig::fcgTSTSettingsNotes_Leave(System::Object^  sender, System::EventArgs^  e) {
    EnableSettingsNoteChange(false);
}
System::Void frmConfig::fcgTSTSettingsNotes_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
    if (e->KeyCode == Keys::Return)
        EnableSettingsNoteChange(false);
}
System::Void frmConfig::fcgTSTSettingsNotes_TextChanged(System::Object^  sender, System::EventArgs^  e) {
    SetfcgTSLSettingsNotes(fcgTSTSettingsNotes->Text);
    CheckOtherChanges(nullptr, nullptr);
}

//////////////////// 追加コマンド関連 /////////////////////////////////////////
System::Void frmConfig::fcgCXCmdExInsert_FontChanged(System::Object^  sender, System::EventArgs^  e) {
    InitCXCmdExInsert();
}
System::Void frmConfig::fcgCXCmdExInsert_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
    String^ insertStr;
    if (       0 == fcgCXCmdExInsert->SelectedIndex) {
        //何もしない
    } else if (1 == fcgCXCmdExInsert->SelectedIndex) {
        //WinXPにおいて、OpenFileDialogはCurrentDirctoryを勝手に変更しやがるので、
        //一度保存し、あとから再適用する
        String^ CurrentDir = Directory::GetCurrentDirectory();
        OpenFileDialog^ ofd = gcnew OpenFileDialog();
        ofd->FileName = L"";
        ofd->Multiselect = false;
        ofd->Filter = L"(*.*)|*.*";
        bool ret = (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK);
        if (ret) {
            if (sys_dat->exstg->s_local.get_relative_path)
                ofd->FileName = GetRelativePath(ofd->FileName, CurrentDir);
            insertStr = ofd->FileName;
        }
        Directory::SetCurrentDirectory(CurrentDir);
    } else {
        insertStr = String(REPLACE_STRINGS_LIST[fcgCXCmdExInsert->SelectedIndex-2].string).ToString();
    }
    if (insertStr != nullptr && insertStr->Length > 0) {
        int current_selection = fcgTXCmdEx->SelectionStart;
        fcgTXCmdEx->Text = fcgTXCmdEx->Text->Insert(fcgTXCmdEx->SelectionStart, insertStr);
        fcgTXCmdEx->SelectionStart = current_selection + insertStr->Length; //たまに変なところへ行くので念のため必要
        fcgTXCmdEx->Focus();
    }
    fcgCXCmdExInsert->SelectedIndex = 0;
}

System::Void frmConfig::AdjustCXDropDownWidth(ComboBox^ CX) {
    System::Drawing::Graphics^ ds = CX->CreateGraphics();
    float maxwidth = 0.0;
    for (int i = 0; i < CX->Items->Count; i++)
        maxwidth = std::max(maxwidth, ds->MeasureString(CX->Items[i]->ToString(), CX->Font).Width);
    CX->DropDownWidth = (int)(maxwidth + 0.5);
    delete ds;
}

System::Void frmConfig::InitCXCmdExInsert() {
    fcgCXCmdExInsert->BeginUpdate();
    fcgCXCmdExInsert->Items->Clear();
    fcgCXCmdExInsert->Items->Add(LOAD_CLI_STRING(AUO_CONFIG_INSERT_STRING));
    fcgCXCmdExInsert->Items->Add(LOAD_CLI_STRING(AUO_CONFIG_FILE_FULL_PATH));
    System::Drawing::Graphics^ ds = fcgCXCmdExInsert->CreateGraphics();
    float max_width_of_string = 0;
    for (int i = 0; REPLACE_STRINGS_LIST[i].desc; i++)
        max_width_of_string = std::max(max_width_of_string, ds->MeasureString(String(REPLACE_STRINGS_LIST[i].string).ToString() + L" … ", fcgCXCmdExInsert->Font).Width);
    for (int i = 0; REPLACE_STRINGS_LIST[i].desc; i++) {
        String^ AppenStr = String(REPLACE_STRINGS_LIST[i].string).ToString();
        const int length_of_string = AppenStr->Length;
        AppenStr += L" … ";
        for (float current_width = 0.0; current_width < max_width_of_string; AppenStr = AppenStr->Insert(length_of_string, L" "))
            current_width = ds->MeasureString(AppenStr, fcgCXCmdExInsert->Font).Width;
        String^ descStr = LOAD_CLI_STRING(REPLACE_STRINGS_LIST[i].mes);
        if (descStr->Length == 0) {
            descStr = String(REPLACE_STRINGS_LIST[i].desc).ToString();
        }
        AppenStr += descStr;
        fcgCXCmdExInsert->Items->Add(AppenStr);
    }
    delete ds;
    fcgCXCmdExInsert->SelectedIndex = 0;
    AdjustCXDropDownWidth(fcgCXCmdExInsert);
    fcgCXCmdExInsert->EndUpdate();
}

/////////////    音声設定関連の関数    ///////////////
System::Void frmConfig::fcgCBAudio2pass_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    if (fcgCBAudio2pass->Checked) {
        fcgCBAudioUsePipe->Checked = false;
        fcgCBAudioUsePipe->Enabled = false;
    } else if (CurrentPipeEnabled) {
        fcgCBAudioUsePipe->Checked = true;
        fcgCBAudioUsePipe->Enabled = true;
    }
}

System::Void frmConfig::fcgCXAudioEncoder_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
    setAudioExtDisplay();
}

System::Void frmConfig::fcgCXAudioEncMode_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
    AudioEncodeModeChanged();
}

System::Int32 frmConfig::GetCurrentAudioDefaultBitrate() {
#if ENCODER_X264 || ENCODER_X265 || ENCODER_SVTAV1
    AUDIO_SETTINGS *astg = &sys_dat->exstg->s_aud_ext[fcgCXAudioEncoder->SelectedIndex];
    const int encMode = fcgCXAudioEncMode->SelectedIndex;
#else
    AUDIO_SETTINGS *astg = (fcgCBAudioUseExt->Checked) ? &sys_dat->exstg->s_aud_ext[std::max(fcgCXAudioEncoder->SelectedIndex, 0)] : &sys_dat->exstg->s_aud_int[std::max(fcgCXAudioEncoderInternal->SelectedIndex, 0)];
    const int encMode = std::max((fcgCBAudioUseExt->Checked) ? fcgCXAudioEncMode->SelectedIndex : fcgCXAudioEncModeInternal->SelectedIndex, 0);
#endif
    return astg->mode[encMode].bitrate_default; 
}

System::Void frmConfig::setAudioExtDisplay() {
    AUDIO_SETTINGS *astg = &sys_dat->exstg->s_aud_ext[fcgCXAudioEncoder->SelectedIndex];
    //～の指定
    if (str_has_char(astg->filename)) {
        fcgLBAudioEncoderPath->Text = String(astg->filename).ToString() + LOAD_CLI_STRING(AUO_CONFIG_SPECIFY_EXE_PATH);
        fcgTXAudioEncoderPath->Enabled = true;
        fcgTXAudioEncoderPath->Text = LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex];
        fcgBTAudioEncoderPath->Enabled = true;
    } else {
        //filename空文字列(wav出力時)
        fcgLBAudioEncoderPath->Text = L"";
        fcgTXAudioEncoderPath->Enabled = false;
        fcgTXAudioEncoderPath->Text = L"";
        fcgBTAudioEncoderPath->Enabled = false;
    }
    fcgTXAudioEncoderPath->SelectionStart = fcgTXAudioEncoderPath->Text->Length;
    fcgCXAudioEncMode->BeginUpdate();
    fcgCXAudioEncMode->Items->Clear();
    for (int i = 0; i < astg->mode_count; i++)
        fcgCXAudioEncMode->Items->Add(String(astg->mode[i].name).ToString());
    fcgCXAudioEncMode->EndUpdate();
    bool pipe_enabled = (astg->pipe_input && (!(fcgCBAudio2pass->Checked && astg->mode[fcgCXAudioEncMode->SelectedIndex].enc_2pass != 0)));
    CurrentPipeEnabled = pipe_enabled;
    fcgCBAudioUsePipe->Enabled = pipe_enabled;
    fcgCBAudioUsePipe->Checked = pipe_enabled;
    if (fcgCXAudioEncMode->Items->Count > 0)
        fcgCXAudioEncMode->SelectedIndex = 0;
}

System::Void frmConfig::AudioEncodeModeChanged() {
    int index = fcgCXAudioEncMode->SelectedIndex;
    AUDIO_SETTINGS *astg = &sys_dat->exstg->s_aud_ext[fcgCXAudioEncoder->SelectedIndex];
    if (astg->mode[index].bitrate) {
        fcgCXAudioEncMode->Width = fcgCXAudioEncModeSmallWidth;
        fcgLBAudioBitrate->Visible = true;
        fcgNUAudioBitrate->Visible = true;
        fcgNUAudioBitrate->Minimum = astg->mode[index].bitrate_min;
        fcgNUAudioBitrate->Maximum = astg->mode[index].bitrate_max;
        fcgNUAudioBitrate->Increment = astg->mode[index].bitrate_step;
        SetNUValue(fcgNUAudioBitrate, (conf->aud.ext.bitrate != 0) ? conf->aud.ext.bitrate : astg->mode[index].bitrate_default);
    } else {
        fcgCXAudioEncMode->Width = fcgCXAudioEncModeLargeWidth;
        fcgLBAudioBitrate->Visible = false;
        fcgNUAudioBitrate->Visible = false;
        fcgNUAudioBitrate->Minimum = 0;
        fcgNUAudioBitrate->Maximum = 65536; //音声の最大レートは1536kbps
    }
    fcgCBAudio2pass->Enabled = astg->mode[index].enc_2pass != 0;
    if (!fcgCBAudio2pass->Enabled) fcgCBAudio2pass->Checked = false;
    SetfbcBTABEnable(fcgNUAudioBitrate->Visible, (int)fcgNUAudioBitrate->Maximum);

    bool delay_cut_available = astg->mode[index].delay > 0;
    fcgLBAudioDelayCut->Visible = delay_cut_available;
    fcgCXAudioDelayCut->Visible = delay_cut_available;
    if (delay_cut_available) {
        const bool delay_cut_edts_available = str_has_char(astg->cmd_raw) && str_has_char(sys_dat->exstg->s_mux[MUXER_MP4_RAW].delay_cmd);
        const int current_idx = fcgCXAudioDelayCut->SelectedIndex;
        const int items_to_set = _countof(AUDIO_DELAY_CUT_MODE) - 1 - ((delay_cut_edts_available) ? 0 : 1);
        fcgCXAudioDelayCut->BeginUpdate();
        fcgCXAudioDelayCut->Items->Clear();
        for (int i = 0; i < items_to_set; i++) {
            String^ string = nullptr;
            if (AUDIO_DELAY_CUT_MODE[i].mes != AUO_MES_UNKNOWN) {
                string = LOAD_CLI_STRING(AUDIO_DELAY_CUT_MODE[i].mes);
            }
            if (string == nullptr || string->Length == 0) {
                string = String(AUDIO_DELAY_CUT_MODE[i].desc).ToString();
            }
            fcgCXAudioDelayCut->Items->Add(string);
        }
        fcgCXAudioDelayCut->EndUpdate();
        fcgCXAudioDelayCut->SelectedIndex = (current_idx >= items_to_set) ? 0 : current_idx;
    } else {
        fcgCXAudioDelayCut->SelectedIndex = 0;
    }
}

///////////////   設定ファイル関連   //////////////////////
System::Void frmConfig::CheckTSItemsEnabled(CONF_GUIEX *current_conf) {
    bool selected = (CheckedStgMenuItem != nullptr);
    fcgTSBSave->Enabled = (selected && memcmp(cnf_stgSelected, current_conf, sizeof(CONF_GUIEX)));
    fcgTSBDelete->Enabled = selected;
}

System::Void frmConfig::UncheckAllDropDownItem(ToolStripItem^ mItem) {
    ToolStripDropDownItem^ DropDownItem = dynamic_cast<ToolStripDropDownItem^>(mItem);
    if (DropDownItem == nullptr)
        return;
    for (int i = 0; i < DropDownItem->DropDownItems->Count; i++) {
        UncheckAllDropDownItem(DropDownItem->DropDownItems[i]);
        ToolStripMenuItem^ item = dynamic_cast<ToolStripMenuItem^>(DropDownItem->DropDownItems[i]);
        if (item != nullptr)
            item->Checked = false;
    }
}

System::Void frmConfig::CheckTSSettingsDropDownItem(ToolStripMenuItem^ mItem) {
    UncheckAllDropDownItem(fcgTSSettings);
    CheckedStgMenuItem = mItem;
    fcgTSSettings->Text = (mItem == nullptr) ? LOAD_CLI_STRING(AUO_CONFIG_PROFILE) : mItem->Text;
    if (mItem != nullptr)
        mItem->Checked = true;
    fcgTSBSave->Enabled = false;
    fcgTSBDelete->Enabled = (mItem != nullptr);
}

ToolStripMenuItem^ frmConfig::fcgTSSettingsSearchItem(String^ stgPath, ToolStripItem^ mItem) {
    if (stgPath == nullptr)
        return nullptr;
    ToolStripDropDownItem^ DropDownItem = dynamic_cast<ToolStripDropDownItem^>(mItem);
    if (DropDownItem == nullptr)
        return nullptr;
    for (int i = 0; i < DropDownItem->DropDownItems->Count; i++) {
        ToolStripMenuItem^ item = fcgTSSettingsSearchItem(stgPath, DropDownItem->DropDownItems[i]);
        if (item != nullptr)
            return item;
        item = dynamic_cast<ToolStripMenuItem^>(DropDownItem->DropDownItems[i]);
        if (item      != nullptr &&
            item->Tag != nullptr &&
            0 == String::Compare(item->Tag->ToString(), stgPath, true))
            return item;
    }
    return nullptr;
}

ToolStripMenuItem^ frmConfig::fcgTSSettingsSearchItem(String^ stgPath) {
    return fcgTSSettingsSearchItem((stgPath != nullptr && stgPath->Length > 0) ? Path::GetFullPath(stgPath) : nullptr, fcgTSSettings);
}

System::Void frmConfig::SaveToStgFile(String^ stgName) {
    size_t nameLen = CountStringBytes(stgName) + 1;
    TCHAR *stg_name = (TCHAR *)malloc(nameLen * sizeof(stg_name[0]));
    GetWCHARfromString(stg_name, (DWORD)nameLen, stgName);
    init_CONF_GUIEX(cnf_stgSelected, fcgCBUsehighbit->Checked);
    FrmToConf(cnf_stgSelected);
    String^ stgDir = Path::GetDirectoryName(stgName);
    if (!Directory::Exists(stgDir))
        Directory::CreateDirectory(stgDir);
    int result = guiEx_config::save_guiEx_conf(cnf_stgSelected, stg_name);
    free(stg_name);
    switch (result) {
        case CONF_ERROR_FILE_OPEN:
            MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_OPEN_STG_FILE), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        case CONF_ERROR_INVALID_FILENAME:
            MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_INVALID_CHAR), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        default:
            break;
    }
    init_CONF_GUIEX(cnf_stgSelected, fcgCBUsehighbit->Checked);
    FrmToConf(cnf_stgSelected);
}

System::Void frmConfig::fcgTSBSave_Click(System::Object^  sender, System::EventArgs^  e) {
    if (CheckedStgMenuItem != nullptr)
        SaveToStgFile(CheckedStgMenuItem->Tag->ToString());
    CheckTSSettingsDropDownItem(CheckedStgMenuItem);
}

System::Void frmConfig::fcgTSBSaveNew_Click(System::Object^  sender, System::EventArgs^  e) {
    frmSaveNewStg::Instance::get()->setStgDir(String(sys_dat->exstg->s_local.stg_dir).ToString());
    frmSaveNewStg::Instance::get()->SetTheme(themeMode, dwStgReader);
    if (CheckedStgMenuItem != nullptr)
        frmSaveNewStg::Instance::get()->setFilename(CheckedStgMenuItem->Text);
    frmSaveNewStg::Instance::get()->ShowDialog();
    String^ stgName = frmSaveNewStg::Instance::get()->StgFileName;
    if (stgName != nullptr && stgName->Length)
        SaveToStgFile(stgName);
    RebuildStgFileDropDown(nullptr);
    CheckTSSettingsDropDownItem(fcgTSSettingsSearchItem(stgName));
}

System::Void frmConfig::DeleteStgFile(ToolStripMenuItem^ mItem) {
    if (System::Windows::Forms::DialogResult::OK ==
        MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ASK_STG_FILE_DELETE) + L"[" + mItem->Text + L"]",
        LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OKCancel, MessageBoxIcon::Exclamation))
    {
        File::Delete(mItem->Tag->ToString());
        RebuildStgFileDropDown(nullptr);
        CheckTSSettingsDropDownItem(nullptr);
        SetfcgTSLSettingsNotes(L"");
    }
}

System::Void frmConfig::fcgTSBDelete_Click(System::Object^  sender, System::EventArgs^  e) {
    DeleteStgFile(CheckedStgMenuItem);
}

System::Void frmConfig::fcgTSSettings_DropDownItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
    ToolStripMenuItem^ ClickedMenuItem = dynamic_cast<ToolStripMenuItem^>(e->ClickedItem);
    if (ClickedMenuItem == nullptr)
        return;
    if (ClickedMenuItem->Tag == nullptr || ClickedMenuItem->Tag->ToString()->Length == 0)
        return;
    CONF_GUIEX load_stg;
    TCHAR stg_path[MAX_PATH_LEN];
    GetWCHARfromString(stg_path, _countof(stg_path), ClickedMenuItem->Tag->ToString());
    if (guiEx_config::load_guiEx_conf(&load_stg, stg_path) == CONF_ERROR_FILE_OPEN) {
        if (MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_OPEN_STG_FILE) + L"\n"
                           + LOAD_CLI_STRING(AUO_CONFIG_ASK_STG_FILE_DELETE),
                           LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::YesNo, MessageBoxIcon::Error)
                           == System::Windows::Forms::DialogResult::Yes)
            DeleteStgFile(ClickedMenuItem);
        return;
    }
    ConfToFrm(&load_stg, true);
    CheckTSSettingsDropDownItem(ClickedMenuItem);
    memcpy(cnf_stgSelected, &load_stg, sizeof(CONF_GUIEX));
}

System::Void frmConfig::RebuildStgFileDropDown(ToolStripDropDownItem^ TS, String^ dir) {
    array<String^>^ subDirs = Directory::GetDirectories(dir);
    for (int i = 0; i < subDirs->Length; i++) {
        ToolStripMenuItem^ DDItem = gcnew ToolStripMenuItem(L"[ " + subDirs[i]->Substring(dir->Length+1) + L" ]");
        DDItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &frmConfig::fcgTSSettings_DropDownItemClicked);
        DDItem->ForeColor = Color::Blue;
        DDItem->Tag = nullptr;
        RebuildStgFileDropDown(DDItem, subDirs[i]);
        TS->DropDownItems->Add(DDItem);
    }
    array<String^>^ stgList = Directory::GetFiles(dir, L"*.stg");
    for (int i = 0; i < stgList->Length; i++) {
        ToolStripMenuItem^ mItem = gcnew ToolStripMenuItem(Path::GetFileNameWithoutExtension(stgList[i]));
        mItem->Tag = stgList[i];
        TS->DropDownItems->Add(mItem);
    }
}

System::Void frmConfig::RebuildStgFileDropDown(String^ stgDir) {
    fcgTSSettings->DropDownItems->Clear();
    if (stgDir != nullptr)
        CurrentStgDir = stgDir;
    if (!Directory::Exists(CurrentStgDir))
        Directory::CreateDirectory(CurrentStgDir);
    RebuildStgFileDropDown(fcgTSSettings, Path::GetFullPath(CurrentStgDir));
}

///////////////   言語ファイル関連   //////////////////////

System::Void frmConfig::CheckTSLanguageDropDownItem(ToolStripMenuItem^ mItem) {
    UncheckAllDropDownItem(fcgTSLanguage);
    fcgTSLanguage->Text = (mItem == nullptr) ? LOAD_CLI_STRING(AuofcgTSSettings) : mItem->Text;
    if (mItem != nullptr)
        mItem->Checked = true;
}
System::Void frmConfig::SetSelectedLanguage(const TCHAR *language_text) {
    for (int i = 0; i < fcgTSLanguage->DropDownItems->Count; i++) {
        ToolStripMenuItem^ item = dynamic_cast<ToolStripMenuItem^>(fcgTSLanguage->DropDownItems[i]);
        TCHAR item_text[MAX_PATH_LEN];
        GetWCHARfromString(item_text, _countof(item_text), item->Tag->ToString());
        if (_tcsncmp(item_text, language_text, _tcslen(language_text)) == 0) {
            CheckTSLanguageDropDownItem(item);
            break;
        }
    }
}

System::Void frmConfig::SaveSelectedLanguage(const TCHAR *language_text) {
    sys_dat->exstg->set_and_save_lang(language_text);
}

System::Void frmConfig::fcgTSLanguage_DropDownItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
    ToolStripMenuItem^ ClickedMenuItem = dynamic_cast<ToolStripMenuItem^>(e->ClickedItem);
    if (ClickedMenuItem == nullptr)
        return;
    if (ClickedMenuItem->Tag == nullptr || ClickedMenuItem->Tag->ToString()->Length == 0)
        return;

    TCHAR language_text[MAX_PATH_LEN];
    GetWCHARfromString(language_text, _countof(language_text), ClickedMenuItem->Tag->ToString());
    SaveSelectedLanguage(language_text);
    load_lng(language_text);
    overwrite_aviutl_ini_auo_info();
    LoadLangText();
    CheckTSLanguageDropDownItem(ClickedMenuItem);
}

System::Void frmConfig::InitLangList() {
    if (list_lng != nullptr) {
        delete list_lng;
    }
#define ENABLE_LNG_FILE_DETECT 1
#if ENABLE_LNG_FILE_DETECT
    auto lnglist = find_lng_files();
    list_lng = new std::vector<tstring>();
    for (const auto& lang : lnglist) {
        list_lng->push_back(lang);
    }
#endif

    fcgTSLanguage->DropDownItems->Clear();

    for (const auto& auo_lang : list_auo_languages) {
        String^ label = String(auo_lang.code).ToString() + L" (" + String(auo_lang.name).ToString() + L")";
        ToolStripMenuItem^ mItem = gcnew ToolStripMenuItem(label);
        mItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &frmConfig::fcgTSLanguage_DropDownItemClicked);
        mItem->Tag = String(auo_lang.code).ToString();
        fcgTSLanguage->DropDownItems->Add(mItem);
    }
#if ENABLE_LNG_FILE_DETECT
    for (size_t i = 0; i < list_lng->size(); i++) {
        auto filename = String(PathFindFileName((*list_lng)[i].c_str())).ToString();
        ToolStripMenuItem^ mItem = gcnew ToolStripMenuItem(filename);
        mItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &frmConfig::fcgTSLanguage_DropDownItemClicked);
        mItem->Tag = filename;
        fcgTSLanguage->DropDownItems->Add(mItem);
    }
#endif
    SetSelectedLanguage(sys_dat->exstg->get_lang());
}

//////////////   初期化関連     ////////////////
System::Void frmConfig::InitData(CONF_GUIEX *set_config, const SYSTEM_DATA *system_data) {
    if (set_config->header.size_all != CONF_INITIALIZED) {
        //初期化されていなければ初期化する
        init_CONF_GUIEX(set_config, FALSE);
    }
    conf = set_config;
    sys_dat = system_data;
}

System::Void frmConfig::InitComboBox() {
    //コンボボックスに値を設定する
    setComboBox(fcgCXAspectRatio,    aspect_desc);
    setComboBox(fcgCXAudioTempDir,   audtempdir_desc);
    setComboBox(fcgCXColorMatrix,    list_colormatrix);
    setComboBox(fcgCXColorPrim,      list_colorprim);
    setComboBox(fcgCXColorRange,     list_color_range);
    setComboBox(fcgCXMP4BoxTempDir,  mp4boxtempdir_desc);
    setComboBox(fcgCXTempDir,        tempdir_desc);
    setComboBox(fcgCXTransfer,       list_transfer);
    setComboBox(fcgCXRC,             list_rc);
    setComboBox(fcgCXEncMode,        list_enc_mode);
    setComboBox(fcgCXSCM,            list_scm);
    setComboBox(fcgCXTune,           list_tune);

    setComboBox(fcgCXAQ,             list_aq);
    setComboBox(fcgCXColorFormat,    list_color_format);
    setComboBox(fcgCXEnableMfmv, list_on_off_default);

    setComboBox(fcgCXHierarchicalLevels, list_hierarchical_levels);
    setComboBox(fcgCXMaxTXSize, list_max_tx_size);

    setComboBox(fcgCXProfileAV1,     list_profile_av1);
    fcgCXProfileAV1->Enabled = false;

    setComboBox(fcgCXAudioEncTiming, audio_enc_timing_desc);
    setComboBox(fcgCXAudioDelayCut,  AUDIO_DELAY_CUT_MODE);

    InitCXCmdExInsert();

    setMuxerCmdExNames(fcgCXMP4CmdEx, MUXER_MP4);
    setMuxerCmdExNames(fcgCXMKVCmdEx, MUXER_MKV);

    setAudioEncoderNames();

    setPriorityList(fcgCXX264Priority);
    setPriorityList(fcgCXMuxPriority);
    setPriorityList(fcgCXAudioPriority);
}

System::Void frmConfig::SetTXMaxLen(TextBox^ TX, int max_len) {
    TX->MaxLength = max_len;
    TX->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &frmConfig::TX_LimitbyBytes);
}

System::Void frmConfig::SetTXMaxLenAll() {
    //MaxLengthに最大文字数をセットし、それをもとにバイト数計算を行うイベントをセットする。
    SetTXMaxLen(fcgTXCmdEx,                _countof(conf->vid.cmdex) - 1);
    SetTXMaxLen(fcgTXX264Path,             _countof(sys_dat->exstg->s_enc.fullpath) - 1);
    SetTXMaxLen(fcgTXX264PathSub,          _countof(sys_dat->exstg->s_enc.fullpath) - 1);
    SetTXMaxLen(fcgTXAudioEncoderPath,     _countof(sys_dat->exstg->s_aud_ext[0].fullpath) - 1);
    SetTXMaxLen(fcgTXMP4MuxerPath,         _countof(sys_dat->exstg->s_mux[MUXER_MP4].fullpath) - 1);
    SetTXMaxLen(fcgTXMKVMuxerPath,         _countof(sys_dat->exstg->s_mux[MUXER_MKV].fullpath) - 1);
    SetTXMaxLen(fcgTXTC2MP4Path,           _countof(sys_dat->exstg->s_mux[MUXER_TC2MP4].fullpath) - 1);
    SetTXMaxLen(fcgTXMP4RawPath,           _countof(sys_dat->exstg->s_mux[MUXER_MP4_RAW].fullpath) - 1);
    SetTXMaxLen(fcgTXCustomTempDir,        _countof(sys_dat->exstg->s_local.custom_tmp_dir) - 1);
    SetTXMaxLen(fcgTXCustomAudioTempDir,   _countof(sys_dat->exstg->s_local.custom_audio_tmp_dir) - 1);
    SetTXMaxLen(fcgTXMP4BoxTempDir,        _countof(sys_dat->exstg->s_local.custom_mp4box_tmp_dir) - 1);
    SetTXMaxLen(fcgTXStatusFile,           _countof(conf->vid.stats) - 1);
    SetTXMaxLen(fcgTXBatBeforeAudioPath,   _countof(conf->oth.batfile.before_audio) - 1);
    SetTXMaxLen(fcgTXBatAfterAudioPath,    _countof(conf->oth.batfile.after_audio) - 1);
    SetTXMaxLen(fcgTXBatBeforePath,        _countof(conf->oth.batfile.before_process) - 1);
    SetTXMaxLen(fcgTXBatAfterPath,         _countof(conf->oth.batfile.after_process) - 1);

    fcgTSTSettingsNotes->MaxLength     =   _countof(conf->oth.notes) - 1;
}

System::Void frmConfig::InitStgFileList() {
    RebuildStgFileDropDown(String(sys_dat->exstg->s_local.stg_dir).ToString());
    stgChanged = false;
    CheckTSSettingsDropDownItem(nullptr);
}

System::Void frmConfig::fcgChangeEnabled(System::Object^  sender, System::EventArgs^  e) {
    fcgLBX264PathSub->Visible = fcgTSBCMDOnly->Checked;
    fcgTXX264PathSub->Visible = fcgTSBCMDOnly->Checked;
    fcgBTX264PathSub->Visible = fcgTSBCMDOnly->Checked;
    fcgBTCmdEx->Visible = !fcgTSBCMDOnly->Checked;
    fcgCBNulOutCLI->Visible = fcgTSBCMDOnly->Checked;
}

System::Void frmConfig::fcgChangeMuxerVisible(System::Object^  sender, System::EventArgs^  e) {
    //tc2mp4のチェック
    const bool enable_tc2mp4_muxer = (0 != str_has_char(sys_dat->exstg->s_mux[MUXER_TC2MP4].base_cmd));
    fcgTXTC2MP4Path->Visible = enable_tc2mp4_muxer;
    fcgLBTC2MP4Path->Visible = enable_tc2mp4_muxer;
    fcgBTTC2MP4Path->Visible = enable_tc2mp4_muxer;
    //mp4 rawのチェック
    const bool enable_mp4raw_muxer = (0 != str_has_char(sys_dat->exstg->s_mux[MUXER_MP4_RAW].base_cmd))
        && wcscmp(sys_dat->exstg->s_mux[MUXER_MP4].dispname, sys_dat->exstg->s_mux[MUXER_MP4_RAW].dispname) != 0;
    fcgTXMP4RawPath->Visible = enable_mp4raw_muxer;
    fcgLBMP4RawPath->Visible = enable_mp4raw_muxer;
    fcgBTMP4RawPath->Visible = enable_mp4raw_muxer;
    //一時フォルダのチェック
    const bool enable_mp4_tmp = (0 != str_has_char(sys_dat->exstg->s_mux[MUXER_MP4].tmp_cmd));
    fcgCXMP4BoxTempDir->Visible = enable_mp4_tmp;
    fcgLBMP4BoxTempDir->Visible = enable_mp4_tmp;
    fcgTXMP4BoxTempDir->Visible = enable_mp4_tmp;
    fcgBTMP4BoxTempDir->Visible = enable_mp4_tmp;
    //Apple Chapterのチェック
    bool enable_mp4_apple_cmdex = false;
    for (int i = 0; i < sys_dat->exstg->s_mux[MUXER_MP4].ex_count; i++)
        enable_mp4_apple_cmdex |= (0 != str_has_char(sys_dat->exstg->s_mux[MUXER_MP4].ex_cmd[i].cmd_apple));
    fcgCBMP4MuxApple->Visible = enable_mp4_apple_cmdex;

    //位置の調整
    static const int HEIGHT = 31;
    fcgLBTC2MP4Path->Location = Point(fcgLBTC2MP4Path->Location.X, fcgLBMP4MuxerPath->Location.Y + HEIGHT * enable_tc2mp4_muxer);
    fcgTXTC2MP4Path->Location = Point(fcgTXTC2MP4Path->Location.X, fcgTXMP4MuxerPath->Location.Y + HEIGHT * enable_tc2mp4_muxer);
    fcgBTTC2MP4Path->Location = Point(fcgBTTC2MP4Path->Location.X, fcgBTMP4MuxerPath->Location.Y + HEIGHT * enable_tc2mp4_muxer);
    fcgLBMP4RawPath->Location = Point(fcgLBMP4RawPath->Location.X, fcgLBTC2MP4Path->Location.Y   + HEIGHT * enable_mp4raw_muxer);
    fcgTXMP4RawPath->Location = Point(fcgTXMP4RawPath->Location.X, fcgTXTC2MP4Path->Location.Y   + HEIGHT * enable_mp4raw_muxer);
    fcgBTMP4RawPath->Location = Point(fcgBTMP4RawPath->Location.X, fcgBTTC2MP4Path->Location.Y   + HEIGHT * enable_mp4raw_muxer);
}

System::Void frmConfig::SetStgEscKey(bool Enable) {
    if (this->KeyPreview == Enable)
        return;
    this->KeyPreview = Enable;
    if (Enable)
        this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmConfig::frmConfig_KeyDown);
    else
        this->KeyDown -= gcnew System::Windows::Forms::KeyEventHandler(this, &frmConfig::frmConfig_KeyDown);
}

System::Void frmConfig::AdjustLocation() {
    //デスクトップ領域(タスクバー等除く)
    System::Drawing::Rectangle screen = System::Windows::Forms::Screen::GetWorkingArea(this);
    //現在のデスクトップ領域の座標
    Point CurrentDesktopLocation = this->DesktopLocation::get();
    //チェック開始
    bool ChangeLocation = false;
    if (CurrentDesktopLocation.X + this->Size.Width > screen.Width) {
        ChangeLocation = true;
        CurrentDesktopLocation.X = clamp(screen.X - this->Size.Width, 4, CurrentDesktopLocation.X);
    }
    if (CurrentDesktopLocation.Y + this->Size.Height > screen.Height) {
        ChangeLocation = true;
        CurrentDesktopLocation.Y = clamp(screen.Y - this->Size.Height, 4, CurrentDesktopLocation.Y);
    }
    if (ChangeLocation) {
        this->StartPosition = FormStartPosition::Manual;
        this->DesktopLocation::set(CurrentDesktopLocation);
    }
}

System::Void frmConfig::fcgCXRC_SelectedIndexChanged(System::Object ^sender, System::EventArgs ^e) {
    int rc_mode = list_rc[fcgCXRC->SelectedIndex].value;
    const bool videoBitrateMode = (x264_encmode_to_RCint[fcgCXRC->SelectedIndex] == ENC_RC_BITRATE);
    fcgNUBitrate->Visible = videoBitrateMode;
    fcgLBKbps->Visible = videoBitrateMode;
    fcgNUQP->Visible = !videoBitrateMode;

    if (rc_mode == -1) { // CRFモード
        fcgNUQP->DecimalPlaces = 2;
        fcgNUQP->Increment = (Decimal)0.25;
        fcgNUQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 70, 0, 0, 0 });
    } else {
        fcgNUQP->DecimalPlaces = 0;
        fcgNUQP->Increment = 1;
        fcgNUQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 63, 0, 0, 0 });
    }
}

System::Void frmConfig::fcgNUQP_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
    int rc_mode = list_rc[fcgCXRC->SelectedIndex].value;
    if (rc_mode == -1) { // CRFモード
        // 0.25単位に丸める
        Decimal value = fcgNUQP->Value;
        Decimal rounded = Math::Round(value / (Decimal)0.25) * (Decimal)0.25;
        if (value != rounded) {
            fcgNUQP->Value = clamp(rounded, fcgNUQP->Minimum, fcgNUQP->Maximum);
        }
    }
}

System::Void frmConfig::InitForm() {
    //UIテーマ切り替え
    CheckTheme();
    //言語設定ファイルのロード
    InitLangList();
    //設定ファイル集の初期化
    InitStgFileList();
    //コンボボックスの値を設定
    InitComboBox();
    //スレッド数上限
    int max_threads_set = (int)(cpu_core_count() * 1.5 + 0.51);
    fcgNUThreads->Maximum = max_threads_set;
    //デフォルトの出力拡張子によってデフォルトのタブを変更
    switch (sys_dat->exstg->s_local.default_output_ext) {
    case 0: //mp4
        fcgtabControlMux->SelectedTab = fcgtabPageMP4;
        break;
    case 1: //mkv
    default:
        fcgtabControlMux->SelectedTab = fcgtabPageMKV;
        break;
    }
    //パラメータセット
    ConfToFrm(conf, true);
    //イベントセット
    SetTXMaxLenAll(); //テキストボックスの最大文字数
    SetAllCheckChangedEvents(this); //変更の確認,ついでにNUの
    //フォームの変更可不可を更新
    fcgChangeMuxerVisible(nullptr, nullptr);
    fcgChangeEnabled(nullptr, nullptr);
    fcgCBAFS_CheckedChanged(nullptr, nullptr);
    EnableSettingsNoteChange(false);
    ExeTXPathLeave();
    //コマンドラインの更新
    fcgRebuildCmd(nullptr, nullptr);
    //表示位置の調整
    AdjustLocation();
    //キー設定
    SetStgEscKey(sys_dat->exstg->s_local.enable_stg_esc_key != 0);
    //フォントの設定
    if (str_has_char(sys_dat->exstg->s_local.conf_font.name))
        SetFontFamilyToForm(this, gcnew FontFamily(String(sys_dat->exstg->s_local.conf_font.name).ToString()), this->Font->FontFamily);
}



System::Void frmConfig::LoadLangText() {
    //一度ウィンドウの再描画を完全に抑止する
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 0, 0);
    //空白時にグレーで入れる文字列を言語変更のため一度空白に戻す
    ExeTXPathEnter();
    //言語更新開始
    LOAD_CLI_TEXT(fcgtabPageSVTAV1_1);
    LOAD_CLI_TEXT(fcgLBFastDecode);
    LOAD_CLI_TEXT(fcgLBTune);
    LOAD_CLI_TEXT(fcgLBOverShootPct);
    LOAD_CLI_TEXT(fcgLBUnderShootPct);
    LOAD_CLI_TEXT(fcgLBMaxSectionPct);
    LOAD_CLI_TEXT(fcgLBMinSectionPct);
    LOAD_CLI_TEXT(fcgLBScm);
    LOAD_CLI_TEXT(fcgLBEnableCDEF);
    LOAD_CLI_TEXT(fcgLBEnableTF);
    LOAD_CLI_TEXT(fcgLBEnableOverlay);
    LOAD_CLI_TEXT(fcgLBEnableDLF);
    LOAD_CLI_TEXT(fcgLBEnableVarianceBoost);
    LOAD_CLI_TEXT(fcgLBEnableRestortionFiltering);
    LOAD_CLI_TEXT(fcgLBFilmGrain);
    LOAD_CLI_TEXT(fcggroupBoxColorMatrix);
    LOAD_CLI_TEXT(fcgLBInputRange);
    LOAD_CLI_TEXT(fcgLBTransfer);
    LOAD_CLI_TEXT(fcgLBColorPrim);
    LOAD_CLI_TEXT(fcgLBColorMatrix);
    LOAD_CLI_TEXT(fcgGroupBoxAspectRatio);
    LOAD_CLI_TEXT(fcgLBAspectRatio);
    LOAD_CLI_TEXT(fcgLBKbps);
    LOAD_CLI_TEXT(fcgLBRC);
    LOAD_CLI_TEXT(fcgLBEncMode);
    LOAD_CLI_TEXT(fcgLB2pasAuto);
    LOAD_CLI_TEXT(fcgLBProfileAV1);
    LOAD_CLI_TEXT(fcgLBColorFormat);
    LOAD_CLI_TEXT(fcgLBAQ);
    LOAD_CLI_TEXT(fcgLBIntraRefreshType);
    LOAD_CLI_TEXT(fcgLBHierarchicalLevels);
    LOAD_CLI_TEXT(fcgLBKeyint);
    LOAD_CLI_TEXT(fcgLBLookahead);
    LOAD_CLI_TEXT(fcgLBLumaQPBias);
    LOAD_CLI_TEXT(fcgLBMaxQP);
    LOAD_CLI_TEXT(fcgLBMinQP);
    LOAD_CLI_TEXT(fcgLBMfmv);
    LOAD_CLI_TEXT(fcgLBMaxTXSize);
    LOAD_CLI_TEXT(fcgLBSceneChangeDetection);
    LOAD_CLI_TEXT(fcgLBSharpness);
    LOAD_CLI_TEXT(fcgLBTFStrength);
    LOAD_CLI_TEXT(fcgLBTile2);
    LOAD_CLI_TEXT(fcgLBTile);
    LOAD_CLI_TEXT(fcgLBVarianceOctile);
    LOAD_CLI_TEXT(fcgLBThreads);
    LOAD_CLI_TEXT(fcgCBUsehighbit);
    LOAD_CLI_TEXT(fcgBTX264Path);
    LOAD_CLI_TEXT(fcgLBX264Path);
    LOAD_CLI_TEXT(fcgtabPageSVTAV1_2);
    LOAD_CLI_TEXT(fcgLBEnableStatReport);
    LOAD_CLI_TEXT(fcgLBSTATUS);
    LOAD_CLI_TEXT(fcgBTStatusFile);
    LOAD_CLI_TEXT(fcgtabPageExSettings);
    LOAD_CLI_TEXT(fcgBTX264PathSub);
    LOAD_CLI_TEXT(fcgLBX264PathSub);
    LOAD_CLI_TEXT(fcgLBTempDir);
    LOAD_CLI_TEXT(fcgBTCustomTempDir);
    LOAD_CLI_TEXT(fcggroupBoxCmdEx);
    LOAD_CLI_TEXT(fcgCBNulOutCLI);
    LOAD_CLI_TEXT(fcgBTCmdEx);
    LOAD_CLI_TEXT(fcgLBX264Priority);
    LOAD_CLI_TEXT(fcggroupBoxExSettings);
    LOAD_CLI_TEXT(fcgCBAuoTcfileout);
    LOAD_CLI_TEXT(fcgCBAFSBitrateCorrection);
    LOAD_CLI_TEXT(fcgCBAFS);
    LOAD_CLI_TEXT(fcgTSExeFileshelp);
    LOAD_CLI_TEXT(fcgtoolStripSettings);
    LOAD_CLI_TEXT(fcgTSBSave);
    LOAD_CLI_TEXT(fcgTSBSaveNew);
    LOAD_CLI_TEXT(fcgTSBDelete);
    LOAD_CLI_TEXT(fcgTSSettings);
    LOAD_CLI_TEXT(fcgTSBCMDOnly);
    LOAD_CLI_TEXT(fcgTSBBitrateCalc);
    LOAD_CLI_TEXT(fcgTSBOtherSettings);
    LOAD_CLI_TEXT(fcgTSLSettingsNotes);
    LOAD_CLI_TEXT(fcgTSTSettingsNotes);
    LOAD_CLI_TEXT(fcgtabPageMP4);
    LOAD_CLI_TEXT(fcgCBMP4MuxApple);
    LOAD_CLI_TEXT(fcgBTTC2MP4Path);
    LOAD_CLI_TEXT(fcgBTMP4MuxerPath);
    LOAD_CLI_TEXT(fcgLBTC2MP4Path);
    LOAD_CLI_TEXT(fcgLBMP4MuxerPath);
    LOAD_CLI_TEXT(fcgLBMP4CmdEx);
    LOAD_CLI_TEXT(fcgCBMP4MuxerExt);
    LOAD_CLI_TEXT(fcgBTMP4RawPath);
    LOAD_CLI_TEXT(fcgLBMP4RawPath);
    LOAD_CLI_TEXT(fcgBTMP4BoxTempDir);
    LOAD_CLI_TEXT(fcgLBMP4BoxTempDir);
    LOAD_CLI_TEXT(fcgtabPageMKV);
    LOAD_CLI_TEXT(fcgBTMKVMuxerPath);
    LOAD_CLI_TEXT(fcgLBMKVMuxerPath);
    LOAD_CLI_TEXT(fcgLBMKVMuxerCmdEx);
    LOAD_CLI_TEXT(fcgCBMKVMuxerExt);
    LOAD_CLI_TEXT(fcgtabPageMux);
    LOAD_CLI_TEXT(fcgLBMuxPriority);
    LOAD_CLI_TEXT(fcgtabPageBat);
    LOAD_CLI_TEXT(fcgLBBatAfterString);
    LOAD_CLI_TEXT(fcgLBBatBeforeString);
    LOAD_CLI_TEXT(fcgBTBatAfterPath);
    LOAD_CLI_TEXT(fcgLBBatAfterPath);
    LOAD_CLI_TEXT(fcgCBWaitForBatAfter);
    LOAD_CLI_TEXT(fcgCBRunBatAfter);
    LOAD_CLI_TEXT(fcgBTBatBeforePath);
    LOAD_CLI_TEXT(fcgLBBatBeforePath);
    LOAD_CLI_TEXT(fcgCBWaitForBatBefore);
    LOAD_CLI_TEXT(fcgCBRunBatBefore);
    LOAD_CLI_TEXT(fcgBTCancel);
    LOAD_CLI_TEXT(fcgBTOK);
    LOAD_CLI_TEXT(fcgBTDefault);
    LOAD_CLI_TEXT(fcgLBVersionDate);
    LOAD_CLI_TEXT(fcgLBVersion);
    LOAD_CLI_TEXT(fcgLBguiExBlog);
    LOAD_CLI_TEXT(fcgtabPageAudioMain);
    LOAD_CLI_TEXT(fcgLBAudioDelayCut);
    LOAD_CLI_TEXT(fcgCBAudioEncTiming);
    LOAD_CLI_TEXT(fcgBTCustomAudioTempDir);
    LOAD_CLI_TEXT(fcgCBAudioUsePipe);
    LOAD_CLI_TEXT(fcgLBAudioBitrate);
    LOAD_CLI_TEXT(fcgCBAudio2pass);
    LOAD_CLI_TEXT(fcgLBAudioEncMode);
    LOAD_CLI_TEXT(fcgBTAudioEncoderPath);
    LOAD_CLI_TEXT(fcgLBAudioEncoderPath);
    LOAD_CLI_TEXT(fcgCBAudioOnly);
    LOAD_CLI_TEXT(fcgCBFAWCheck);
    LOAD_CLI_TEXT(fcgLBAudioEncoder);
    LOAD_CLI_TEXT(fcgLBAudioTemp);
    LOAD_CLI_TEXT(fcgtabPageAudioOther);
    LOAD_CLI_TEXT(fcgLBBatAfterAudioString);
    LOAD_CLI_TEXT(fcgLBBatBeforeAudioString);
    LOAD_CLI_TEXT(fcgBTBatAfterAudioPath);
    LOAD_CLI_TEXT(fcgLBBatAfterAudioPath);
    LOAD_CLI_TEXT(fcgCBRunBatAfterAudio);
    LOAD_CLI_TEXT(fcgBTBatBeforeAudioPath);
    LOAD_CLI_TEXT(fcgLBBatBeforeAudioPath);
    LOAD_CLI_TEXT(fcgCBRunBatBeforeAudio);
    LOAD_CLI_TEXT(fcgLBAudioPriority);
    //LOAD_CLI_MAIN_TEXT(fcgMain);

    //ローカル設定のロード(ini変更を反映)
    LoadLocalStg();
    //ローカル設定の反映
    SetLocalStg();
    //コンボボックスの値を設定
    InitComboBox();
    //ツールチップ
    SetHelpToolTips();
    SetX264VersionToolTip(LocalStg.x264Path);
    ActivateToolTip(sys_dat->exstg->s_local.disable_tooltip_help == FALSE);
    //タイムコードのappendix(後付修飾子)を反映
    fcgCBAuoTcfileout->Text = LOAD_CLI_STRING(AUO_CONFIG_TC_FILE_OUT) + L" (" + String(sys_dat->exstg->s_append.tc).ToString() + L")";
    { //タイトル表示,バージョン情報,コンパイル日時
        auto auo_full_name = g_auo_mes.get(AUO_GUIEX_FULL_NAME);
        if (auo_full_name == nullptr || wcslen(auo_full_name) == 0) auo_full_name = AUO_FULL_NAME_W;
        this->Text = String(auo_full_name).ToString();
        fcgLBVersion->Text = String(auo_full_name).ToString() + L" " + String(AUO_VERSION_STR_W).ToString();
        fcgLBVersionDate->Text = L"build " + String(__DATE__).ToString() + L" " + String(__TIME__).ToString();
    }
    //空白時にグレーで入れる文字列を言語に即して復活させる
    ExeTXPathLeave();
    //一度ウィンドウの再描画を再開し、強制的に再描画させる
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 1, 0);
    this->Refresh();
}

/////////////         データ <-> GUI     /////////////
System::Void frmConfig::ConfToFrm(CONF_GUIEX *cnf, bool all) {
    //ひたすら書くだけ。めんどい
    CONF_ENC enc;
    parse_cmd(&enc, cnf->enc.cmd, true);
    this->SuspendLayout();
    fcgCBUsehighbit->Checked = enc.bit_depth > 8;
    SetCXIndex(fcgCXRC, get_cx_index(list_rc, enc.rc));
    SetCXIndex(fcgCXEncMode, get_cx_index(list_enc_mode, enc.preset));
    SetNUValue(fcgNUQP, enc.qp);
    SetNUValue(fcgNUBitrate, enc.bitrate);
    fcgCB2PassAuto->Checked = enc.pass > 0;

    SetCXIndex(fcgCXAQ, get_cx_index(list_aq, enc.aq));        //aq
    SetCXIndex(fcgCXColorFormat, get_cx_index(list_color_format, enc.output_csp));
    SetCXIndex(fcgCXColorPrim, get_cx_index(list_colorprim, enc.color_primaries));
    SetCXIndex(fcgCXColorRange, get_cx_index(list_color_range, enc.color_range));
    fcgCBEnableCDEF->Checked = enc.enable_cdef != 0;
    fcgCBEnableDLF->Checked = enc.enable_dlf != 0;
    SetCXIndex(fcgCXEnableMfmv, get_cx_index(list_on_off_default, enc.enable_mfmv));
    fcgCBEnableOverlay->Checked = enc.enable_overlays != 0;
    fcgCBEnableRestorationFilter->Checked = enc.enable_restoration != 0;
    fcgCBEnableStatReport->Checked = enc.enable_stat_report != 0;
    SetNUValue(fcgNUEnableTF, enc.enable_tf);
    fcgCBFastDecode->Checked = enc.fast_decode != 0;
    SetNUValue(fcgNUFilmGrain, enc.film_grain);
    SetCXIndex(fcgCXHierarchicalLevels, get_cx_index(list_hierarchical_levels, enc.hierarchical_levels)); //hierarchical-levels
    SetNUValue(fcgNUIntraRefreshType, enc.intra_refresh_type);
    SetNUValue(fcgNUKeyint, enc.keyint);        //intra-period
    SetNUValue(fcgNUThreads, enc.lp);         //lp (LogicalProcessorNumber)
    SetNUValue(fcgNULookahead, enc.lookahead);
    SetNUValue(fcgNULumaQPBias, enc.luminance_qp_bias);
    SetCXIndex(fcgCXColorMatrix, get_cx_index(list_colormatrix, enc.matrix_coefficients));
    SetNUValue(fcgNUMaxQP, enc.max_qp);
    SetCXIndex(fcgCXMaxTXSize, get_cx_index(list_max_tx_size, enc.max_tx_size));
    SetNUValue(fcgNUMaxSectionPct, enc.maxsection_pct);
    SetNUValue(fcgNUMinQP, enc.min_qp);
    SetNUValue(fcgNUMinSectionPct, enc.minsection_pct);
    SetNUValue(fcgNUOverShootPct, enc.overshoot_pct);
    SetCXIndex(fcgCXProfileAV1, get_cx_index(list_profile_av1, 0 /*enc.profile*/));
    SetNUValue(fcgNUSharpness, enc.sharpness);
    fcgCBSceneChangeDetection->Checked = enc.scd != 0;  //scd
    SetCXIndex(fcgCXSCM, get_cx_index(list_scm, enc.scm));        //scm
    SetNUValue(fcgNUTFStrength, enc.tf_strength);
    SetNUValue(fcgNUTileRows, enc.tile_rows);   //tile-rows
    SetNUValue(fcgNUTileColumns, enc.tile_columns); //tile-columns
    SetCXIndex(fcgCXTune, get_cx_index(list_tune, enc.tune));
    SetCXIndex(fcgCXTransfer, get_cx_index(list_transfer, enc.transfer_characteristics));
    SetNUValue(fcgNUUnderShootPct, enc.undershoot_pct);
    SetNUValue(fcgNUVarianceBoostStrength, enc.enable_variance_boost ? enc.variance_boost_strength : 0);
    SetNUValue(fcgNUVarianceOctile, enc.variance_octile);

    if (cnf->enc.sar_x * cnf->enc.sar_y < 0)
        cnf->enc.sar_x = cnf->enc.sar_y = 0;
    fcgCXAspectRatio->SelectedIndex = (cnf->enc.sar_x < 0);
    SetNUValue(fcgNUAspectRatioX, abs(cnf->enc.sar_x));
    SetNUValue(fcgNUAspectRatioY, abs(cnf->enc.sar_y));

    if (all) {
        fcgTXStatusFile->Text = (str_has_char(cnf->vid.stats))     ? String(cnf->vid.stats).ToString() : String(DefaultStatusFilePath).ToString();

        fcgCBAFS->Checked                  = cnf->vid.afs != 0;
        fcgCBAFSBitrateCorrection->Checked = cnf->vid.afs_bitrate_correction != 0;
        SetCXIndex(fcgCXX264Priority,        cnf->vid.priority);
        SetCXIndex(fcgCXTempDir,             cnf->oth.temp_dir);

        fcgTXCmdEx->Text            = String(cnf->vid.cmdex).ToString();

        //音声
        fcgCBAudioOnly->Checked            = cnf->oth.out_audio_only != 0;
        fcgCBFAWCheck->Checked             = cnf->aud.ext.faw_check != 0;
        SetCXIndex(fcgCXAudioEncoder,        cnf->aud.ext.encoder);
        fcgCBAudio2pass->Checked           = cnf->aud.ext.use_2pass != 0;
        fcgCBAudioUsePipe->Checked = (CurrentPipeEnabled && !cnf->aud.ext.use_wav);
        SetCXIndex(fcgCXAudioDelayCut,       cnf->aud.ext.delay_cut);
        SetCXIndex(fcgCXAudioEncMode,        cnf->aud.ext.enc_mode);
        SetNUValue(fcgNUAudioBitrate,       (cnf->aud.ext.bitrate != 0) ? cnf->aud.ext.bitrate : GetCurrentAudioDefaultBitrate());
        SetCXIndex(fcgCXAudioPriority,       cnf->aud.ext.priority);
        SetCXIndex(fcgCXAudioTempDir,        cnf->aud.ext.aud_temp_dir);
        SetCXIndex(fcgCXAudioEncTiming,      cnf->aud.ext.audio_encode_timing);
        fcgCBRunBatBeforeAudio->Checked    =(cnf->oth.run_bat & RUN_BAT_BEFORE_AUDIO) != 0;
        fcgCBRunBatAfterAudio->Checked     =(cnf->oth.run_bat & RUN_BAT_AFTER_AUDIO) != 0;
        fcgTXBatBeforeAudioPath->Text      = String(cnf->oth.batfile.before_audio).ToString();
        fcgTXBatAfterAudioPath->Text       = String(cnf->oth.batfile.after_audio).ToString();

        //mux
        fcgCBMP4MuxerExt->Checked          = cnf->mux.disable_mp4ext == 0;
        fcgCBMP4MuxApple->Checked          = cnf->mux.apple_mode != 0;
        SetCXIndex(fcgCXMP4CmdEx,            cnf->mux.mp4_mode);
        SetCXIndex(fcgCXMP4BoxTempDir,       cnf->mux.mp4_temp_dir);
        fcgCBMKVMuxerExt->Checked          = cnf->mux.disable_mkvext == 0;
        SetCXIndex(fcgCXMKVCmdEx,            cnf->mux.mkv_mode);
        SetCXIndex(fcgCXMuxPriority,         cnf->mux.priority);

        fcgCBRunBatBefore->Checked         =(cnf->oth.run_bat & RUN_BAT_BEFORE_PROCESS) != 0;
        fcgCBRunBatAfter->Checked          =(cnf->oth.run_bat & RUN_BAT_AFTER_PROCESS)  != 0;
        fcgCBWaitForBatBefore->Checked     =(cnf->oth.dont_wait_bat_fin & RUN_BAT_BEFORE_PROCESS) == 0;
        fcgCBWaitForBatAfter->Checked      =(cnf->oth.dont_wait_bat_fin & RUN_BAT_AFTER_PROCESS)  == 0;
        fcgTXBatBeforePath->Text           = String(cnf->oth.batfile.before_process).ToString();
        fcgTXBatAfterPath->Text            = String(cnf->oth.batfile.after_process).ToString();

        SetfcgTSLSettingsNotes(cnf->oth.notes);

        //cli mode
        fcgTSBCMDOnly->Checked             = cnf->oth.disable_guicmd != 0;
    }

    this->ResumeLayout();
    this->PerformLayout();
}

String ^frmConfig::FrmToConf(CONF_GUIEX *cnf) {
    //これもひたすら書くだけ。めんどい
    CONF_ENC enc = get_default_prm();
    //x264部
    enc.bit_depth            = fcgCBUsehighbit->Checked ? 10 : 8;
    enc.rc                   = list_rc[fcgCXRC->SelectedIndex].value;
    enc.enable_tpl_la        = (enc.rc == get_cx_value(list_rc, L"CQP")) ? 0 : 1;
    enc.preset               = list_enc_mode[fcgCXEncMode->SelectedIndex].value;
    enc.bitrate              = (int)fcgNUBitrate->Value;
    enc.qp                   = (float)fcgNUQP->Value;
    enc.pass                 = (int)fcgCB2PassAuto->Checked ? 2 : 0;

    enc.aq = list_aq[fcgCXAQ->SelectedIndex].value;
    enc.output_csp = list_color_format[fcgCXColorFormat->SelectedIndex].value;
    enc.color_primaries = list_colorprim[fcgCXColorPrim->SelectedIndex].value;
    enc.color_range = list_color_range[fcgCXColorRange->SelectedIndex].value;

    enc.enable_cdef = fcgCBEnableCDEF->Checked;
    enc.enable_dlf = fcgCBEnableDLF->Checked;

    enc.enable_mfmv = list_on_off_default[fcgCXEnableMfmv->SelectedIndex].value;
    enc.enable_overlays = fcgCBEnableOverlay->Checked;
    enc.enable_restoration = fcgCBEnableRestorationFilter->Checked;

    enc.enable_stat_report = fcgCBEnableStatReport->Checked;
    enc.enable_tf = (int)fcgNUEnableTF->Value;
    enc.enable_variance_boost = ((int)fcgNUVarianceBoostStrength->Value) != 0 ? 1 : 0;

    enc.fast_decode = fcgCBFastDecode->Checked;
    enc.film_grain = (int)fcgNUFilmGrain->Value;
    enc.hierarchical_levels = (int)list_hierarchical_levels[fcgCXHierarchicalLevels->SelectedIndex].value;
    enc.intra_refresh_type = (int)fcgNUIntraRefreshType->Value;
    enc.keyint = (int)fcgNUKeyint->Value;
    enc.lp = (int)fcgNUThreads->Value;
    enc.lookahead = (int)fcgNULookahead->Value;
    enc.luminance_qp_bias = (int)fcgNULumaQPBias->Value;
    enc.matrix_coefficients = list_colormatrix[fcgCXColorMatrix->SelectedIndex].value;
    enc.max_qp = (int)fcgNUMaxQP->Value;
    enc.max_tx_size = list_max_tx_size[fcgCXMaxTXSize->SelectedIndex].value;
    enc.maxsection_pct = (int)fcgNUMaxSectionPct->Value;
    enc.min_qp = (int)fcgNUMinQP->Value;
    enc.minsection_pct = (int)fcgNUMinSectionPct->Value;

    enc.overshoot_pct = (int)fcgNUOverShootPct->Value;
    enc.profile = list_profile_av1[fcgCXProfileAV1->SelectedIndex].value;
    enc.sharpness = (int)fcgNUSharpness->Value;
    enc.scd = fcgCBSceneChangeDetection->Checked;
    enc.scm = list_scm[fcgCXSCM->SelectedIndex].value;

    enc.tf_strength = (int)fcgNUTFStrength->Value;
    enc.tile_rows = (int)fcgNUTileRows->Value;
    enc.tile_columns = (int)fcgNUTileColumns->Value;
    enc.transfer_characteristics = list_transfer[fcgCXTransfer->SelectedIndex].value;
    enc.tune = list_tune[fcgCXTune->SelectedIndex].value;
    enc.undershoot_pct = (int)fcgNUUnderShootPct->Value;
    enc.variance_boost_strength = (int)fcgNUVarianceBoostStrength->Value;
    enc.variance_octile = (int)fcgNUVarianceOctile->Value;

    cnf->enc.sar_x = (int)fcgNUAspectRatioX->Value * ((fcgCXAspectRatio->SelectedIndex != 1) ? 1 : -1);
    cnf->enc.sar_y = (int)fcgNUAspectRatioY->Value * ((fcgCXAspectRatio->SelectedIndex != 1) ? 1 : -1);

    //拡張部
    GetWCHARfromString(cnf->vid.stats, fcgTXStatusFile->Text);
    cnf->vid.afs                    = fcgCBAFS->Checked;
    cnf->vid.afs_bitrate_correction = fcgCBAFSBitrateCorrection->Checked;
    cnf->vid.priority               = fcgCXX264Priority->SelectedIndex;
    cnf->oth.temp_dir               = fcgCXTempDir->SelectedIndex;
    GetWCHARfromString(cnf->vid.cmdex, fcgTXCmdEx->Text);

    //音声部
    cnf->oth.out_audio_only             = fcgCBAudioOnly->Checked;
    cnf->aud.use_internal               = FALSE;
    cnf->aud.ext.encoder                = fcgCXAudioEncoder->SelectedIndex;
    cnf->aud.ext.faw_check              = fcgCBFAWCheck->Checked;
    cnf->aud.ext.enc_mode               = fcgCXAudioEncMode->SelectedIndex;
    cnf->aud.ext.bitrate                = (int)fcgNUAudioBitrate->Value;
    cnf->aud.ext.use_2pass              = fcgCBAudio2pass->Checked;
    cnf->aud.ext.use_wav                = !fcgCBAudioUsePipe->Checked;
    cnf->aud.ext.delay_cut              = fcgCXAudioDelayCut->SelectedIndex;
    cnf->aud.ext.priority               = fcgCXAudioPriority->SelectedIndex;
    cnf->aud.ext.audio_encode_timing    = fcgCXAudioEncTiming->SelectedIndex;
    cnf->aud.ext.aud_temp_dir           = fcgCXAudioTempDir->SelectedIndex;

    //mux部
    cnf->mux.disable_mp4ext         = !fcgCBMP4MuxerExt->Checked;
    cnf->mux.apple_mode             = fcgCBMP4MuxApple->Checked;
    cnf->mux.mp4_mode               = fcgCXMP4CmdEx->SelectedIndex;
    cnf->mux.mp4_temp_dir           = fcgCXMP4BoxTempDir->SelectedIndex;
    cnf->mux.disable_mkvext         = !fcgCBMKVMuxerExt->Checked;
    cnf->mux.mkv_mode               = fcgCXMKVCmdEx->SelectedIndex;
    cnf->mux.priority               = fcgCXMuxPriority->SelectedIndex;

    cnf->oth.run_bat                = RUN_BAT_NONE;
    cnf->oth.run_bat               |= (fcgCBRunBatBeforeAudio->Checked) ? RUN_BAT_BEFORE_AUDIO   : NULL;
    cnf->oth.run_bat               |= (fcgCBRunBatAfterAudio->Checked)  ? RUN_BAT_AFTER_AUDIO    : NULL;
    cnf->oth.run_bat               |= (fcgCBRunBatBefore->Checked)      ? RUN_BAT_BEFORE_PROCESS : NULL;
    cnf->oth.run_bat               |= (fcgCBRunBatAfter->Checked)       ? RUN_BAT_AFTER_PROCESS  : NULL;
    cnf->oth.dont_wait_bat_fin      = RUN_BAT_NONE;
    cnf->oth.dont_wait_bat_fin     |= (!fcgCBWaitForBatBefore->Checked) ? RUN_BAT_BEFORE_PROCESS : NULL;
    cnf->oth.dont_wait_bat_fin     |= (!fcgCBWaitForBatAfter->Checked)  ? RUN_BAT_AFTER_PROCESS  : NULL;
    GetWCHARfromString(cnf->oth.batfile.before_process, fcgTXBatBeforePath->Text);
    GetWCHARfromString(cnf->oth.batfile.after_process,  fcgTXBatAfterPath->Text);
    GetWCHARfromString(cnf->oth.batfile.before_audio,   fcgTXBatBeforeAudioPath->Text);
    GetWCHARfromString(cnf->oth.batfile.after_audio,    fcgTXBatAfterAudioPath->Text);

    GetfcgTSLSettingsNotes(cnf->oth.notes, _countof(cnf->oth.notes));
    _tcscpy_s(cnf->enc.cmd, gen_cmd(&enc, true).c_str());

    //cli mode
    cnf->oth.disable_guicmd         = fcgTSBCMDOnly->Checked;

    return String(gen_cmd(&enc, false).c_str()).ToString();
}

System::Void frmConfig::GetfcgTSLSettingsNotes(TCHAR *notes, int nSize) {
    ZeroMemory(notes, nSize);
    if (fcgTSLSettingsNotes->Overflow != ToolStripItemOverflow::Never)
        GetWCHARfromString(notes, nSize, fcgTSLSettingsNotes->Text);
}

System::Void frmConfig::SetfcgTSLSettingsNotes(const TCHAR *notes) {
    if (_tcschr(notes, _T('\0')) != nullptr) {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[0][0], StgNotesColor[0][1], StgNotesColor[0][2]);
        fcgTSLSettingsNotes->Text = String(notes).ToString();
        fcgTSLSettingsNotes->Overflow = ToolStripItemOverflow::AsNeeded;
    } else {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[1][0], StgNotesColor[1][1], StgNotesColor[1][2]);
        fcgTSLSettingsNotes->Text = LOAD_CLI_STRING(AuofcgTSTSettingsNotes);
        fcgTSLSettingsNotes->Overflow = ToolStripItemOverflow::Never;
    }
}

System::Void frmConfig::SetfcgTSLSettingsNotes(String^ notes) {
    if (notes->Length && fcgTSLSettingsNotes->Overflow != ToolStripItemOverflow::Never) {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[0][0], StgNotesColor[0][1], StgNotesColor[0][2]);
        fcgTSLSettingsNotes->Text = notes;
        fcgTSLSettingsNotes->Overflow = ToolStripItemOverflow::AsNeeded;
    } else {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[1][0], StgNotesColor[1][1], StgNotesColor[1][2]);
        fcgTSLSettingsNotes->Text = LOAD_CLI_STRING(AuofcgTSTSettingsNotes);
        fcgTSLSettingsNotes->Overflow = ToolStripItemOverflow::Never;
    }
}

System::Void frmConfig::SetChangedEvent(Control^ control, System::EventHandler^ _event) {
    System::Type^ ControlType = control->GetType();
    if (ControlType == NumericUpDown::typeid)
        ((NumericUpDown^)control)->ValueChanged += _event;
    else if (ControlType == ComboBox::typeid)
        ((ComboBox^)control)->SelectedIndexChanged += _event;
    else if (ControlType == CheckBox::typeid)
        ((CheckBox^)control)->CheckedChanged += _event;
    else if (ControlType == TextBox::typeid)
        ((TextBox^)control)->TextChanged += _event;
}

System::Void frmConfig::SetToolStripEvents(ToolStrip^ TS, System::Windows::Forms::MouseEventHandler^ _event) {
    for (int i = 0; i < TS->Items->Count; i++) {
        ToolStripButton^ TSB = dynamic_cast<ToolStripButton^>(TS->Items[i]);
        if (TSB != nullptr) TSB->MouseDown += _event;
    }
}

System::Void frmConfig::TabControl_DarkDrawItem(System::Object^ sender, DrawItemEventArgs^ e) {
    //対象のTabControlを取得
    TabControl^ tab = dynamic_cast<TabControl^>(sender);
    //タブページのテキストを取得
    System::String^ txt = tab->TabPages[e->Index]->Text;

    //タブのテキストと背景を描画するためのブラシを決定する
    SolidBrush^ foreBrush = gcnew System::Drawing::SolidBrush(ColorfromInt(DEFAULT_UI_COLOR_TEXT_DARK));
    SolidBrush^ backBrush = gcnew System::Drawing::SolidBrush(ColorfromInt(DEFAULT_UI_COLOR_BASE_DARK));

    //StringFormatを作成
    StringFormat^ sf = gcnew System::Drawing::StringFormat();
    //中央に表示する
    sf->Alignment = StringAlignment::Center;
    sf->LineAlignment = StringAlignment::Center;

    //背景の描画
    e->Graphics->FillRectangle(backBrush, e->Bounds);
    //Textの描画
    e->Graphics->DrawString(txt, e->Font, foreBrush, e->Bounds, sf);
}

System::Void frmConfig::fcgMouseEnter_SetColor(System::Object^  sender, System::EventArgs^  e) {
    fcgMouseEnterLeave_SetColor(sender, themeMode, DarkenWindowState::Hot, dwStgReader);
}
System::Void frmConfig::fcgMouseLeave_SetColor(System::Object^  sender, System::EventArgs^  e) {
    fcgMouseEnterLeave_SetColor(sender, themeMode, DarkenWindowState::Normal, dwStgReader);
}

System::Void frmConfig::SetAllMouseMove(Control ^top, const AuoTheme themeTo) {
    if (themeTo == themeMode) return;
    System::Type^ type = top->GetType();
    if (type == CheckBox::typeid /* || isToolStripItem(type)*/) {
        top->MouseEnter += gcnew System::EventHandler(this, &frmConfig::fcgMouseEnter_SetColor);
        top->MouseLeave += gcnew System::EventHandler(this, &frmConfig::fcgMouseLeave_SetColor);
    } else if (type == ToolStrip::typeid) {
        ToolStrip^ TS = dynamic_cast<ToolStrip^>(top);
        for (int i = 0; i < TS->Items->Count; i++) {
            auto item = TS->Items[i];
            item->MouseEnter += gcnew System::EventHandler(this, &frmConfig::fcgMouseEnter_SetColor);
            item->MouseLeave += gcnew System::EventHandler(this, &frmConfig::fcgMouseLeave_SetColor);
        }
    }
    for (int i = 0; i < top->Controls->Count; i++) {
        SetAllMouseMove(top->Controls[i], themeTo);
    }
}

System::Void frmConfig::CheckTheme() {
    AuoTheme themeTo = AuoTheme::DefaultLight;
    try {
        //DarkenWindowが使用されていれば設定をロードする
        if (dwStgReader != nullptr) delete dwStgReader;
        const auto [theme, dwStg] = check_current_theme(sys_dat->aviutl_dir);
        if (dwStg == nullptr) return;
        themeTo = theme;
        dwStgReader = dwStg;
        //変更の必要がなければ終了
        if (themeTo == themeMode) return;
    } catch (...) {
        return;
    }

    //一度ウィンドウの再描画を完全に抑止する
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 0, 0);
#if 1
    //tabcontrolのborderを隠す
    SwitchComboBoxBorder(fcgtabControlVideo, fcgPNHideTabControlVideo, themeMode, themeTo, dwStgReader);
    SwitchComboBoxBorder(fcgtabControlAudio, fcgPNHideTabControlAudio, themeMode, themeTo, dwStgReader);
    SwitchComboBoxBorder(fcgtabControlMux,   fcgPNHideTabControlMux,   themeMode, themeTo, dwStgReader);
    //上部のtoolstripborderを隠すためのパネル
    fcgPNHideToolStripBorder->Visible = themeTo == AuoTheme::DarkenWindowDark;
#endif
#if 0
    //TabControlをオーナードローする
    fcgtabControlVideo->DrawMode = TabDrawMode::OwnerDrawFixed;
    fcgtabControlVideo->DrawItem += gcnew DrawItemEventHandler(this, &frmConfig::TabControl_DarkDrawItem);

    fcgtabControlAudio->DrawMode = TabDrawMode::OwnerDrawFixed;
    fcgtabControlAudio->DrawItem += gcnew DrawItemEventHandler(this, &frmConfig::TabControl_DarkDrawItem);

    fcgtabControlMux->DrawMode = TabDrawMode::OwnerDrawFixed;
    fcgtabControlMux->DrawItem += gcnew DrawItemEventHandler(this, &frmConfig::TabControl_DarkDrawItem);
#endif
    if (themeTo != themeMode) {
        SetAllColor(this, themeTo, this->GetType(), dwStgReader);
        SetAllMouseMove(this, themeTo);
    }
    //一度ウィンドウの再描画を再開し、強制的に再描画させる
    SendMessage(reinterpret_cast<HWND>(this->Handle.ToPointer()), WM_SETREDRAW, 1, 0);
    this->Refresh();
    themeMode = themeTo;
}

System::Void frmConfig::SetAllCheckChangedEvents(Control ^top) {
    //再帰を使用してすべてのコントロールのtagを調べ、イベントをセットする
    for (int i = 0; i < top->Controls->Count; i++) {
        System::Type^ type = top->Controls[i]->GetType();
        if (type == NumericUpDown::typeid)
            top->Controls[i]->Enter += gcnew System::EventHandler(this, &frmConfig::NUSelectAll);

        if (type == Label::typeid || type == Button::typeid)
            ;
        else if (type == ToolStrip::typeid)
            SetToolStripEvents((ToolStrip^)(top->Controls[i]), gcnew System::Windows::Forms::MouseEventHandler(this, &frmConfig::fcgTSItem_MouseDown));
        else if (top->Controls[i]->Tag == nullptr)
            SetAllCheckChangedEvents(top->Controls[i]);
        else if (String::Equals(top->Controls[i]->Tag->ToString(), L"reCmd"))
            SetChangedEvent(top->Controls[i], gcnew System::EventHandler(this, &frmConfig::fcgRebuildCmd));
        else if (String::Equals(top->Controls[i]->Tag->ToString(), L"chValue"))
            SetChangedEvent(top->Controls[i], gcnew System::EventHandler(this, &frmConfig::CheckOtherChanges));
        else
            SetAllCheckChangedEvents(top->Controls[i]);
    }
}

System::Void frmConfig::SetHelpToolTipsColorMatrix(Control^ control, const char *type) {
    fcgTTX264->SetToolTip(control, L"--" + String(type).ToString() + L"\n"
        + LOAD_CLI_STRING(AuofrmTTColorMatrix1) + L"\n"
        + LOAD_CLI_STRING(AuofrmTTColorMatrix2) + L"\n"
        + LOAD_CLI_STRING(AuofrmTTColorMatrix3) + L" " + COLOR_MATRIX_THRESHOLD + L" " + LOAD_CLI_STRING(AuofrmTTColorMatrix4) + L" … bt709\n"
        + LOAD_CLI_STRING(AuofrmTTColorMatrix3) + L" " + COLOR_MATRIX_THRESHOLD + L" " + LOAD_CLI_STRING(AuofrmTTColorMatrix5) + L" … bt601\n"
        + LOAD_CLI_STRING(AuofrmTTColorMatrix6)
    );
}

System::Void frmConfig::SetHelpToolTips() {
    //x264基本
#define SET_TOOL_TIP_SVTAV1(target, x) { fcgTTX264->SetToolTip(target, LOAD_CLI_STRING(AuofrmTT ## x)); }
#define SET_TOOL_TIP_EX2(target, x) { fcgTTEx->SetToolTip(target, LOAD_CLI_STRING(AuofrmTT ## x)); }
#define SET_TOOL_TIP_EX(target) { fcgTTEx->SetToolTip(target, LOAD_CLI_STRING(AuofrmTT ## target)); }

    SET_TOOL_TIP_SVTAV1(fcgCBUsehighbit, fcgCBUsehighbit);
    SET_TOOL_TIP_SVTAV1(fcgBTX264Path, fcgBTX264Path);
    SET_TOOL_TIP_SVTAV1(fcgBTX264PathSub, fcgBTX264Path);

    //色空間
    SetHelpToolTipsColorMatrix(fcgCXColorMatrix, "colormatrix");
    SetHelpToolTipsColorMatrix(fcgCXColorPrim,   "colorprim");
    SetHelpToolTipsColorMatrix(fcgCXTransfer,    "transfer");
    //fcgTTX264->SetToolTip(fcgCXInputRange,      L"--input-range\n"
    //    + L"\n"
    //    + L"\"" + String(list_input_range[0].desc).ToString() + L"\"  [デフォルト]\n"
    //    + L"  output-csp yuv系 … tv色調 (圧縮レンジ)\n"
    //    + L"  output-csp rgb系 … pc色調\n"
    //    + L"\n"
    //    + L"\"" + String(list_input_range[1].desc).ToString() + L"\"\n"
    //    + L"  pc色調 (フルレンジ)"
    //    );

    fcgTTX264->SetToolTip(fcgCXAspectRatio, L""
        + LOAD_CLI_STRING(aspect_desc[0].mes) + L"\n"
        + L"   " + LOAD_CLI_STRING(AuofrmTTfcgCXAspectRatioSAR) + L"\n"
        + L"\n"
        + LOAD_CLI_STRING(aspect_desc[1].mes) + L"\n"
        + L"   " + LOAD_CLI_STRING(AuofrmTTfcgCXAspectRatioDAR) + L"\n"
    );
    SET_TOOL_TIP_SVTAV1(fcgNUAspectRatioX, fcgNUAspectRatioX);
    SET_TOOL_TIP_SVTAV1(fcgNUAspectRatioY, fcgNUAspectRatioY);
    fcgTTX264->SetToolTip(fcgNUThreads,          L"--threads\n"
        + LOAD_CLI_STRING(AuofrmTTZeroAsAuto)
        );

    //拡張
    SET_TOOL_TIP_EX(fcgCBAFS);
    SET_TOOL_TIP_EX(fcgCBAFSBitrateCorrection);
    SET_TOOL_TIP_EX(fcgCBAuoTcfileout);
    //SET_TOOL_TIP_EX(fcgCBCheckKeyframes);
    //SET_TOOL_TIP_EX(fcgCBSetKeyframeAtChapter);
    //SET_TOOL_TIP_EX(fcgCBInputAsLW48);
    SET_TOOL_TIP_EX(fcgCXTempDir);
    SET_TOOL_TIP_EX(fcgBTCustomTempDir);
    SET_TOOL_TIP_EX(fcgBTCmdEx);

    //音声
    SET_TOOL_TIP_EX(fcgCXAudioEncoder);
    SET_TOOL_TIP_EX(fcgCBAudioOnly);
    SET_TOOL_TIP_EX(fcgCBFAWCheck);
    SET_TOOL_TIP_EX(fcgBTAudioEncoderPath);
    SET_TOOL_TIP_EX(fcgCXAudioEncMode);
    SET_TOOL_TIP_EX(fcgCBAudio2pass);
    SET_TOOL_TIP_EX(fcgCBAudioUsePipe);
    SET_TOOL_TIP_EX(fcgNUAudioBitrate);
    SET_TOOL_TIP_EX(fcgCXAudioPriority);
    SET_TOOL_TIP_EX(fcgCXAudioEncTiming);
    SET_TOOL_TIP_EX(fcgCXAudioTempDir);
    SET_TOOL_TIP_EX(fcgBTCustomAudioTempDir);
    //音声バッチファイル実行
    SET_TOOL_TIP_EX(fcgCBRunBatBeforeAudio);
    SET_TOOL_TIP_EX(fcgCBRunBatAfterAudio);
    SET_TOOL_TIP_EX(fcgBTBatBeforeAudioPath);
    SET_TOOL_TIP_EX(fcgBTBatAfterAudioPath);

    //muxer
    SET_TOOL_TIP_EX(fcgCBMP4MuxerExt);
    SET_TOOL_TIP_EX(fcgCXMP4CmdEx);
    SET_TOOL_TIP_EX(fcgBTMP4MuxerPath);
    SET_TOOL_TIP_EX(fcgBTTC2MP4Path);
    SET_TOOL_TIP_EX(fcgBTMP4RawPath);
    SET_TOOL_TIP_EX(fcgCXMP4BoxTempDir);
    SET_TOOL_TIP_EX(fcgBTMP4BoxTempDir);
    SET_TOOL_TIP_EX(fcgCBMKVMuxerExt);
    SET_TOOL_TIP_EX(fcgCXMKVCmdEx);
    SET_TOOL_TIP_EX(fcgBTMKVMuxerPath);
    SET_TOOL_TIP_EX(fcgCXMuxPriority);
    //バッチファイル実行
    SET_TOOL_TIP_EX(fcgCBRunBatBefore);
    SET_TOOL_TIP_EX(fcgCBRunBatAfter);
    SET_TOOL_TIP_EX(fcgCBWaitForBatBefore);
    SET_TOOL_TIP_EX(fcgCBWaitForBatAfter);
    SET_TOOL_TIP_EX(fcgBTBatBeforePath);
    SET_TOOL_TIP_EX(fcgBTBatAfterPath);
    //他
    SET_TOOL_TIP_EX(fcgTXCmd);
    SET_TOOL_TIP_EX(fcgBTDefault);
    //上部ツールストリップ
    fcgTSBCMDOnly->ToolTipText = LOAD_CLI_STRING(AuofrmTTfcgTSBCMDOnly);
    fcgTSBDelete->ToolTipText = LOAD_CLI_STRING(AuofrmTTfcgTSBDelete);
    fcgTSBOtherSettings->ToolTipText = LOAD_CLI_STRING(AuofrmTTfcgTSBOtherSettings);
    fcgTSBSave->ToolTipText = LOAD_CLI_STRING(AuofrmTTfcgTSBSave);
    fcgTSBSaveNew->ToolTipText = LOAD_CLI_STRING(AuofrmTTfcgTSBSaveNew);
}
System::Void frmConfig::SetX264VersionToolTip(String^ x264Path) {
    String^ mes;
    if (File::Exists(x264Path)) {
        char mes_buf[2560];
        TCHAR exe_path[MAX_PATH_LEN];
        GetWCHARfromString(exe_path, _countof(exe_path), x264Path);
        if (get_exe_message(exe_path, _T("--version"), mes_buf, _countof(mes_buf), AUO_PIPE_MUXED) == RP_SUCCESS)
            mes = String(mes_buf).ToString();
        else
            mes = LOAD_CLI_STRING(AUO_CONFIG_ERR_GET_EXE_VER);
    } else {
        mes = LOAD_CLI_STRING(AUO_CONFIG_ERR_EXE_NOT_FOUND);
    }
    fcgTTX264Version->SetToolTip(fcgTXX264Path, mes);
    fcgTTX264Version->SetToolTip(fcgTXX264PathSub, mes);
}
System::Void frmConfig::ShowExehelp(String^ ExePath, String^ args) {
    if (!File::Exists(ExePath)) {
        MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_EXE_NOT_FOUND), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
    } else {
        TCHAR exe_path[MAX_PATH_LEN];
        TCHAR file_path[MAX_PATH_LEN];
        TCHAR cmd[MAX_CMD_LEN];
        GetWCHARfromString(exe_path, _countof(exe_path), ExePath);
        apply_appendix(file_path, _countof(file_path), exe_path, _T("_fullhelp.txt"));
        File::Delete(String(file_path).ToString());
        array<String^>^ arg_list = args->Split(L';');
        for (int i = 0; i < arg_list->Length; i++) {
            if (i) {
                StreamWriter^ sw;
                try {
                    sw = gcnew StreamWriter(String(file_path).ToString(), true, System::Text::Encoding::GetEncoding("shift_jis"));
                    sw->WriteLine();
                    sw->WriteLine();
                } catch (...) {
                    //ファイルオープンに失敗…初回のget_exe_message_to_fileでエラーとなるため、おそらく起こらない
                } finally {
                    if (sw != nullptr) { sw->Close(); }
                }
            }
            GetWCHARfromString(cmd, _countof(cmd), arg_list[i]);
            if (get_exe_message_to_file(exe_path, cmd, file_path, AUO_PIPE_MUXED, 5) != RP_SUCCESS) {
                File::Delete(String(file_path).ToString());
                MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_GET_HELP), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
        }
        try {
            System::Diagnostics::Process::Start(String(file_path).ToString());
        } catch (...) {
            MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_ERR_OPEN_HELP), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}


#pragma warning( pop )