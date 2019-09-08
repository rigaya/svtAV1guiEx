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
        MessageBox::Show(L"ファイル名に使用できない文字が含まれています。\n保存できません。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
    if (String::Compare(Path::GetExtension(stgName), L".stg", true))
        stgName += L".stg";
    if (File::Exists(fileName = Path::Combine(fsnCXFolderBrowser->GetSelectedFolder(), stgName)))
        if (MessageBox::Show(stgName + L" はすでに存在します。上書きしますか?", L"上書き確認", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
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
System::Void frmBitrateCalculator::Init(int VideoBitrate, int AudioBitrate, bool BTVBEnable, bool BTABEnable, int ab_max) {
    guiEx_settings exStg(true);
    exStg.load_fbc();
    enable_events = false;
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

/// -------------------------------------------------
///     frmConfig 関数  (frmBitrateCalculator関連)
/// -------------------------------------------------
System::Void frmConfig::CloseBitrateCalc() {
    frmBitrateCalculator::Instance::get()->Close();
}
System::Void frmConfig::fcgTSBBitrateCalc_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    if (fcgTSBBitrateCalc->Checked) {
        int videoBitrate = (int)fcgNUBitrate->Value;
        bool videoBitrateMode = (x264_encmode_to_RCint[fcgCXRC->SelectedIndex] == X264_RC_BITRATE);

        frmBitrateCalculator::Instance::get()->Init(
            (videoBitrateMode) ? videoBitrate : 0,
            (fcgNUAudioBitrate->Visible) ? (int)fcgNUAudioBitrate->Value : 0,
            videoBitrateMode,
            fcgNUAudioBitrate->Visible,
            (int)fcgNUAudioBitrate->Maximum
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
    if (x264_encmode_to_RCint[fcgCXRC->SelectedIndex] == X264_RC_BITRATE)
        fcgNUBitrate->Value = bitrate;
}

System::Void frmConfig::SetAudioBitrate(int bitrate) {
    SetNUValue(fcgNUAudioBitrate, bitrate);
}
System::Void frmConfig::InformfbcClosed() {
    fcgTSBBitrateCalc->Checked = false;
}
#

/// -------------------------------------------------
///     frmUpdate 関数
/// -------------------------------------------------
System::Void frmConfig::fcgTSBUpdate_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
#if ENABLE_AUOSETUP
    if (fcgTSBUpdate->Checked)
        frmExeUpdate->Show();
    else
        frmExeUpdate->Visible = false; //Close()してしまうとfrmExeUpdateがDisposeされてしまう
#endif
}

System::Void frmConfig::fcgTSBUpdate_CheckFinished(String^ mes) {
#if ENABLE_AUOSETUP
    //更新をチェックした時間を保存する
    if (this->InvokeRequired) {
        this->Invoke(gcnew svtAV1guiEx::DelegateProcessFin(this, &frmConfig::fcgTSBUpdate_CheckFinished), mes);
        return;
    }

    guiEx_settings stg;
    stg.load_encode_stg();
    GetCHARfromString(stg.s_local.last_update_check, _countof(stg.s_local.last_update_check), DateTime::Now.ToString());
    stg.save_local();

    if (auoSetupControl::checkIfUpdateAvailable(mes)) {
        fcgTSBUpdate->Text = L"更新*";
        fcgTSBUpdate->ForeColor = Color::MediumSlateBlue;
    }
#endif
}

System::Void frmConfig::fcgTSBUpdate_UpdateFinished(String^ mes) {
#if ENABLE_AUOSETUP
    if (this->InvokeRequired) {
        this->Invoke(gcnew svtAV1guiEx::DelegateProcessFin(this, &frmConfig::fcgTSBUpdate_UpdateFinished), mes);
        return;
    }

    fcgTSBUpdate->Text = L"更新";
    fcgTSBUpdate->ForeColor = SystemColors::ControlText;

    //更新にしたがって表示を更新する
    guiEx_settings stg;
    stg.load_encode_stg();
    LocalStg.x264Path        = String(stg.s_enc.fullpath).ToString();
    LocalStg.MP4MuxerPath    = String(stg.s_mux[MUXER_MP4].fullpath).ToString();
    LocalStg.TC2MP4Path      = String(stg.s_mux[MUXER_TC2MP4].fullpath).ToString();
    LocalStg.MP4RawPath      = String(stg.s_mux[MUXER_MP4_RAW].fullpath).ToString();
    LocalStg.audEncPath[DEFAULT_AUDIO_ENCODER] = String(stg.s_aud[DEFAULT_AUDIO_ENCODER].fullpath).ToString();
    LocalStg.audEncPath[DEFAULT_AUDIO_ENCODER+1] = String(stg.s_aud[DEFAULT_AUDIO_ENCODER+1].fullpath).ToString();

    SetLocalStg();
    if (fcgCXAudioEncoder->SelectedIndex == DEFAULT_AUDIO_ENCODER
        || fcgCXAudioEncoder->SelectedIndex == (DEFAULT_AUDIO_ENCODER+1)) {
        fcgTXAudioEncoderPath->Text = LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex];
    }
#endif
}

System::Void frmConfig::InformfruClosed() {
    fcgTSBUpdate->Checked = false;
}

#if ENABLE_AUOSETUP
System::Void frmUpdate::frmUpdate_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
    e->Cancel = true;
    this->Visible = false; //Close()してしまうとfrmExeUpdateがDisposeされてしまう
    frmConfig^ fcg = dynamic_cast<frmConfig^>(this->Owner);
    if (fcg != nullptr)
        fcg->InformfruClosed();
}
#endif

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
    LocalStg.MPGMuxerExeName = String(_ex_stg->s_mux[MUXER_MPG].filename).ToString();
    LocalStg.MPGMuxerPath    = String(_ex_stg->s_mux[MUXER_MPG].fullpath).ToString();
    LocalStg.MP4RawExeName   = String(_ex_stg->s_mux[MUXER_MP4_RAW].filename).ToString();
    LocalStg.MP4RawPath      = String(_ex_stg->s_mux[MUXER_MP4_RAW].fullpath).ToString();

    LocalStg.audEncName->Clear();
    LocalStg.audEncExeName->Clear();
    LocalStg.audEncPath->Clear();
    for (int i = 0; i < _ex_stg->s_aud_count; i++) {
        LocalStg.audEncName->Add(String(_ex_stg->s_aud[i].dispname).ToString());
        LocalStg.audEncExeName->Add(String(_ex_stg->s_aud[i].filename).ToString());
        LocalStg.audEncPath->Add(String(_ex_stg->s_aud[i].fullpath).ToString());
    }
    if (_ex_stg->s_local.large_cmdbox)
        fcgTXCmd_DoubleClick(nullptr, nullptr); //初期状態は縮小なので、拡大
}

System::Boolean frmConfig::CheckLocalStg() {
    bool error = false;
    String^ err = "";
    //x264のチェック
    if (!File::Exists(LocalStg.x264Path)) {
        error = true;
        err += L"指定された SvtAv1EncApp は存在しません。\n [ " + LocalStg.x264Path + L" ]\n";
    }
    //音声エンコーダのチェック (実行ファイル名がない場合はチェックしない)
    if (LocalStg.audEncExeName[fcgCXAudioEncoder->SelectedIndex]->Length) {
        String^ AudioEncoderPath = LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex];
        if (!File::Exists(AudioEncoderPath)
            && (fcgCXAudioEncoder->SelectedIndex != sys_dat->exstg->s_aud_faw_index
                || !check_if_faw2aac_exists()) ) {
            //音声実行ファイルがない かつ
            //選択された音声がfawでない または fawであってもfaw2aacがない
            if (error) err += L"\n\n";
            error = true;
            err += L"指定された 音声エンコーダ は存在しません。\n [ " + AudioEncoderPath + L" ]\n";
        }
    }
    //FAWのチェック
    if (fcgCBFAWCheck->Checked) {
        if (sys_dat->exstg->s_aud_faw_index == FAW_INDEX_ERROR) {
            if (error) err += L"\n\n";
            error = true;
            err += L"FAWCheckが選択されましたが、svtAV1guiEx.ini から\n"
                + L"FAW の設定を読み込めませんでした。\n"
                + L"svtAV1guiEx.ini を確認してください。\n";
        } else if (!File::Exists(LocalStg.audEncPath[sys_dat->exstg->s_aud_faw_index])
                   && !check_if_faw2aac_exists()) {
            //fawの実行ファイルが存在しない かつ faw2aacも存在しない
            if (error) err += L"\n\n";
            error = true;
            err += L"FAWCheckが選択されましたが、FAW(fawcl)へのパスが正しく指定されていません。\n"
                +  L"一度設定画面でFAW(fawcl)へのパスを指定してください。\n";
        }
    }
    //自動マルチパスの自動ビットレート設定のチェック
    if (fcgLBAMPAutoBitrate != nullptr && fcgLBAMPAutoBitrate->Visible) {
        if (error) err += L"\n\n";
        error = true;
        err += L"目標映像ビットレートを自動に設定するには、\n"
            + L"上限ビットレート、上限ファイルサイズの少なくとも片方を\n"
            + L"適切に設定する必要があります。\n"
            + L"上限ビットレート、上限ファイルサイズの設定を見なおしてください。";
    }
    if (error)
        MessageBox::Show(this, err, L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
    return error;
}

System::Void frmConfig::SaveLocalStg() {
    guiEx_settings *_ex_stg = sys_dat->exstg;
    _ex_stg->load_encode_stg();
    _ex_stg->s_local.large_cmdbox = fcgTXCmd->Multiline;
    GetCHARfromString(_ex_stg->s_enc.fullpath,               sizeof(_ex_stg->s_enc.fullpath),               LocalStg.x264Path);
    GetCHARfromString(_ex_stg->s_local.custom_tmp_dir,        sizeof(_ex_stg->s_local.custom_tmp_dir),        LocalStg.CustomTmpDir);
    GetCHARfromString(_ex_stg->s_local.custom_mp4box_tmp_dir, sizeof(_ex_stg->s_local.custom_mp4box_tmp_dir), LocalStg.CustomMP4TmpDir);
    GetCHARfromString(_ex_stg->s_local.custom_audio_tmp_dir,  sizeof(_ex_stg->s_local.custom_audio_tmp_dir),  LocalStg.CustomAudTmpDir);
    GetCHARfromString(_ex_stg->s_local.app_dir,               sizeof(_ex_stg->s_local.app_dir),               LocalStg.LastAppDir);
    GetCHARfromString(_ex_stg->s_local.bat_dir,               sizeof(_ex_stg->s_local.bat_dir),               LocalStg.LastBatDir);
    GetCHARfromString(_ex_stg->s_mux[MUXER_MP4].fullpath,     sizeof(_ex_stg->s_mux[MUXER_MP4].fullpath),     LocalStg.MP4MuxerPath);
    GetCHARfromString(_ex_stg->s_mux[MUXER_MKV].fullpath,     sizeof(_ex_stg->s_mux[MUXER_MKV].fullpath),     LocalStg.MKVMuxerPath);
    GetCHARfromString(_ex_stg->s_mux[MUXER_TC2MP4].fullpath,  sizeof(_ex_stg->s_mux[MUXER_TC2MP4].fullpath),  LocalStg.TC2MP4Path);
    GetCHARfromString(_ex_stg->s_mux[MUXER_MPG].fullpath,     sizeof(_ex_stg->s_mux[MUXER_MPG].fullpath),     LocalStg.MPGMuxerPath);
    GetCHARfromString(_ex_stg->s_mux[MUXER_MP4_RAW].fullpath, sizeof(_ex_stg->s_mux[MUXER_MP4_RAW].fullpath), LocalStg.MP4RawPath);
    for (int i = 0; i < _ex_stg->s_aud_count; i++)
        GetCHARfromString(_ex_stg->s_aud[i].fullpath,         sizeof(_ex_stg->s_aud[i].fullpath),             LocalStg.audEncPath[i]);
    _ex_stg->save_local();
}

System::Void frmConfig::SetLocalStg() {
    fcgLBX264Path->Text           = L"SvtAv1EncApp.exe の指定";
    fcgLBX264PathSub->Text        = L"SvtAv1EncApp.exe の指定";
    fcgTXX264Path->Text           = LocalStg.x264Path;
    fcgTXX264PathSub->Text        = LocalStg.x264Path;
    fcgTXMP4MuxerPath->Text       = LocalStg.MP4MuxerPath;
    fcgTXMKVMuxerPath->Text       = LocalStg.MKVMuxerPath;
    fcgTXTC2MP4Path->Text         = LocalStg.TC2MP4Path;
    fcgTXMPGMuxerPath->Text       = LocalStg.MPGMuxerPath;
    fcgTXMP4RawPath->Text         = LocalStg.MP4RawPath;
    fcgTXCustomAudioTempDir->Text = LocalStg.CustomAudTmpDir;
    fcgTXCustomTempDir->Text      = LocalStg.CustomTmpDir;
    fcgTXMP4BoxTempDir->Text      = LocalStg.CustomMP4TmpDir;
    fcgLBMP4MuxerPath->Text       = LocalStg.MP4MuxerExeName + L" の指定";
    fcgLBMKVMuxerPath->Text       = LocalStg.MKVMuxerExeName + L" の指定";
    fcgLBTC2MP4Path->Text         = LocalStg.TC2MP4ExeName   + L" の指定";
    fcgLBMPGMuxerPath->Text       = LocalStg.MPGMuxerExeName + L" の指定";
    fcgLBMP4RawPath->Text         = LocalStg.MP4RawExeName + L" の指定";

    fcgTXX264Path->SelectionStart           = fcgTXX264Path->Text->Length;
    fcgTXX264PathSub->SelectionStart        = fcgTXX264PathSub->Text->Length;
    fcgTXMP4MuxerPath->SelectionStart       = fcgTXMP4MuxerPath->Text->Length;
    fcgTXTC2MP4Path->SelectionStart         = fcgTXTC2MP4Path->Text->Length;
    fcgTXMKVMuxerPath->SelectionStart       = fcgTXMKVMuxerPath->Text->Length;
    fcgTXMPGMuxerPath->SelectionStart       = fcgTXMPGMuxerPath->Text->Length;
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
    frmOtherSettings::Instance::get()->ShowDialog();
    char buf[MAX_PATH_LEN];
    GetCHARfromString(buf, sizeof(buf), frmOtherSettings::Instance::get()->stgDir);
    if (_stricmp(buf, sys_dat->exstg->s_local.stg_dir)) {
        //変更があったら保存する
        strcpy_s(sys_dat->exstg->s_local.stg_dir, sizeof(sys_dat->exstg->s_local.stg_dir), buf);
        sys_dat->exstg->save_local();
        InitStgFileList();
    }
    //再読み込み
    guiEx_settings stg;
    stg.load_encode_stg();
    log_reload_settings();
    sys_dat->exstg->s_local.default_audio_encoder = stg.s_local.default_audio_encoder;
    sys_dat->exstg->s_local.get_relative_path = stg.s_local.get_relative_path;
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
        fcgtabControlVideo->TabPages->RemoveAt(0);
        fcgtabPageExSettings->Text = L"映像";
        fcggroupBoxCmdEx->Text = L"コマンドライン";
    } else {
        fcgtabControlVideo->TabPages->Insert(0, fcgtabPageX264Main);
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

    int muxer_cmdex = fcgCXMP4CmdEx->SelectedIndex;
    setMuxerCmdExNames(fcgCXMP4CmdEx, (fcgCBAFS->Checked) ? MUXER_TC2MP4 : MUXER_MP4);
    fcgCXMP4CmdEx->SelectedIndex = muxer_cmdex;
}

System::Boolean frmConfig::EnableSettingsNoteChange(bool Enable) {
    if (fcgTSTSettingsNotes->Visible == Enable &&
        fcgTSLSettingsNotes->Visible == !Enable)
        return true;
    if (CountStringBytes(fcgTSTSettingsNotes->Text) > fcgTSTSettingsNotes->MaxLength - 1) {
        MessageBox::Show(this, L"入力された文字数が多すぎます。減らしてください。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
        fcgTSTSettingsNotes->Focus();
        fcgTSTSettingsNotes->SelectionStart = fcgTSTSettingsNotes->Text->Length;
        return false;
    }
    fcgTSTSettingsNotes->Visible = Enable;
    fcgTSLSettingsNotes->Visible = !Enable;
    if (Enable) {
        fcgTSTSettingsNotes->Text = fcgTSLSettingsNotes->Text;
        fcgTSTSettingsNotes->Focus();
        bool isDefaultNote = String::Compare(fcgTSTSettingsNotes->Text, String(DefaultStgNotes).ToString()) == 0;
        fcgTSTSettingsNotes->Select((isDefaultNote) ? 0 : fcgTSTSettingsNotes->Text->Length, fcgTSTSettingsNotes->Text->Length);
    } else {
        SetfcgTSLSettingsNotes(fcgTSTSettingsNotes->Text);
        CheckOtherChanges(nullptr, nullptr);
    }
    return true;
}
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
        maxwidth = max(maxwidth, ds->MeasureString(CX->Items[i]->ToString(), CX->Font).Width);
    CX->DropDownWidth = (int)(maxwidth + 0.5);
    delete ds;
}

System::Void frmConfig::InitCXCmdExInsert() {
    fcgCXCmdExInsert->BeginUpdate();
    fcgCXCmdExInsert->Items->Clear();
    fcgCXCmdExInsert->Items->Add(L"文字列を挿入...");
    fcgCXCmdExInsert->Items->Add(L"ファイル フルパス...");
    System::Drawing::Graphics^ ds = fcgCXCmdExInsert->CreateGraphics();
    float max_width_of_string = 0;
    for (int i = 0; REPLACE_STRINGS_LIST[i].desc; i++)
        max_width_of_string = max(max_width_of_string, ds->MeasureString(String(REPLACE_STRINGS_LIST[i].string).ToString() + L" … ", fcgCXCmdExInsert->Font).Width);
    for (int i = 0; REPLACE_STRINGS_LIST[i].desc; i++) {
        String^ AppenStr = String(REPLACE_STRINGS_LIST[i].string).ToString();
        const int length_of_string = AppenStr->Length;
        AppenStr += L" … ";
        for (float current_width = 0.0; current_width < max_width_of_string; AppenStr = AppenStr->Insert(length_of_string, L" "))
            current_width = ds->MeasureString(AppenStr, fcgCXCmdExInsert->Font).Width;
        AppenStr += String(REPLACE_STRINGS_LIST[i].desc).ToString();
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
    setAudioDisplay();
}

System::Void frmConfig::fcgCXAudioEncMode_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
    AudioEncodeModeChanged();
}

System::Int32 frmConfig::GetCurrentAudioDefaultBitrate() {
    return sys_dat->exstg->s_aud[fcgCXAudioEncoder->SelectedIndex].mode[fcgCXAudioEncMode->SelectedIndex].bitrate_default;
}

System::Void frmConfig::setAudioDisplay() {
    AUDIO_SETTINGS *astg = &sys_dat->exstg->s_aud[fcgCXAudioEncoder->SelectedIndex];
    //～の指定
    if (str_has_char(astg->filename)) {
        fcgLBAudioEncoderPath->Text = String(astg->filename).ToString() + L" の指定";
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
    AUDIO_SETTINGS *astg = &sys_dat->exstg->s_aud[fcgCXAudioEncoder->SelectedIndex];
    if (astg->mode[index].bitrate) {
        fcgCXAudioEncMode->Width = fcgCXAudioEncModeSmallWidth;
        fcgLBAudioBitrate->Visible = true;
        fcgNUAudioBitrate->Visible = true;
        fcgNUAudioBitrate->Minimum = astg->mode[index].bitrate_min;
        fcgNUAudioBitrate->Maximum = astg->mode[index].bitrate_max;
        fcgNUAudioBitrate->Increment = astg->mode[index].bitrate_step;
        SetNUValue(fcgNUAudioBitrate, (conf->aud.bitrate != 0) ? conf->aud.bitrate : astg->mode[index].bitrate_default);
    } else {
        fcgCXAudioEncMode->Width = fcgCXAudioEncModeLargeWidth;
        fcgLBAudioBitrate->Visible = false;
        fcgNUAudioBitrate->Visible = false;
        fcgNUAudioBitrate->Minimum = 0;
        fcgNUAudioBitrate->Maximum = 1536; //音声の最大レートは1536kbps
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
        for (int i = 0; i < items_to_set; i++)
            fcgCXAudioDelayCut->Items->Add(String(AUDIO_DELAY_CUT_MODE[i]).ToString());
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
    fcgTSSettings->Text = (mItem == nullptr) ? L"プロファイル" : mItem->Text;
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
    char *stg_name = (char *)malloc(nameLen);
    GetCHARfromString(stg_name, nameLen, stgName);
    init_CONF_GUIEX(cnf_stgSelected);
    FrmToConf(cnf_stgSelected);
    String^ stgDir = Path::GetDirectoryName(stgName);
    if (!Directory::Exists(stgDir))
        Directory::CreateDirectory(stgDir);
    guiEx_config exCnf;
    int result = exCnf.save_guiEx_conf(cnf_stgSelected, stg_name);
    free(stg_name);
    switch (result) {
        case CONF_ERROR_FILE_OPEN:
            MessageBox::Show(L"設定ファイルオープンに失敗しました。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        case CONF_ERROR_INVALID_FILENAME:
            MessageBox::Show(L"ファイル名に使用できない文字が含まれています。\n保存できません。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        default:
            break;
    }
    init_CONF_GUIEX(cnf_stgSelected);
    FrmToConf(cnf_stgSelected);
}

System::Void frmConfig::fcgTSBSave_Click(System::Object^  sender, System::EventArgs^  e) {
    if (CheckedStgMenuItem != nullptr)
        SaveToStgFile(CheckedStgMenuItem->Tag->ToString());
    CheckTSSettingsDropDownItem(CheckedStgMenuItem);
}

System::Void frmConfig::fcgTSBSaveNew_Click(System::Object^  sender, System::EventArgs^  e) {
    frmSaveNewStg::Instance::get()->setStgDir(String(sys_dat->exstg->s_local.stg_dir).ToString());
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
        MessageBox::Show(L"設定ファイル " + mItem->Text + L" を削除してよろしいですか?",
        L"エラー", MessageBoxButtons::OKCancel, MessageBoxIcon::Exclamation))
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
    guiEx_config exCnf;
    char stg_path[MAX_PATH_LEN];
    GetCHARfromString(stg_path, sizeof(stg_path), ClickedMenuItem->Tag->ToString());
    if (exCnf.load_guiEx_conf(&load_stg, stg_path) == CONF_ERROR_FILE_OPEN) {
        if (MessageBox::Show(L"設定ファイルオープンに失敗しました。\n"
                           + L"このファイルを削除しますか?",
                           L"エラー", MessageBoxButtons::YesNo, MessageBoxIcon::Error)
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

//////////////   初期化関連     ////////////////
System::Void frmConfig::InitData(CONF_GUIEX *set_config, const SYSTEM_DATA *system_data) {
    if (set_config->size_all != CONF_INITIALIZED) {
        //初期化されていなければ初期化する
        init_CONF_GUIEX(set_config);
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
    setComboBox(fcgCXInputRange,     list_input_range);
    setComboBox(fcgCXMP4BoxTempDir,  mp4boxtempdir_desc);
    setComboBox(fcgCXTempDir,        tempdir_desc);
    setComboBox(fcgCXTransfer,       list_transfer);
    setComboBox(fcgCXRC,             x264_encodemode_desc);
    setComboBox(fcgCXEncMode,        list_enc_mode);
    setComboBox(fcgCXSCM,            list_scm);
    setComboBox(fcgCXAQ,             list_aq);

    setComboBox(fcgCXAudioEncTiming, audio_enc_timing_desc);
    setComboBox(fcgCXAudioDelayCut,  AUDIO_DELAY_CUT_MODE);

    InitCXCmdExInsert();

    setMuxerCmdExNames(fcgCXMP4CmdEx, MUXER_MP4);
    setMuxerCmdExNames(fcgCXMKVCmdEx, MUXER_MKV);
    setMuxerCmdExNames(fcgCXMPGCmdEx, MUXER_MPG);

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
    SetTXMaxLen(fcgTXCmdEx,                sizeof(conf->vid.cmdex) - 1);
    SetTXMaxLen(fcgTXX264Path,             sizeof(sys_dat->exstg->s_enc.fullpath) - 1);
    SetTXMaxLen(fcgTXX264PathSub,          sizeof(sys_dat->exstg->s_enc.fullpath) - 1);
    SetTXMaxLen(fcgTXAudioEncoderPath,     sizeof(sys_dat->exstg->s_aud[0].fullpath) - 1);
    SetTXMaxLen(fcgTXMP4MuxerPath,         sizeof(sys_dat->exstg->s_mux[MUXER_MP4].fullpath) - 1);
    SetTXMaxLen(fcgTXMKVMuxerPath,         sizeof(sys_dat->exstg->s_mux[MUXER_MKV].fullpath) - 1);
    SetTXMaxLen(fcgTXTC2MP4Path,           sizeof(sys_dat->exstg->s_mux[MUXER_TC2MP4].fullpath) - 1);
    SetTXMaxLen(fcgTXMPGMuxerPath,         sizeof(sys_dat->exstg->s_mux[MUXER_MPG].fullpath) - 1);
    SetTXMaxLen(fcgTXMP4RawPath,           sizeof(sys_dat->exstg->s_mux[MUXER_MP4_RAW].fullpath) - 1);
    SetTXMaxLen(fcgTXCustomTempDir,        sizeof(sys_dat->exstg->s_local.custom_tmp_dir) - 1);
    SetTXMaxLen(fcgTXCustomAudioTempDir,   sizeof(sys_dat->exstg->s_local.custom_audio_tmp_dir) - 1);
    SetTXMaxLen(fcgTXMP4BoxTempDir,        sizeof(sys_dat->exstg->s_local.custom_mp4box_tmp_dir) - 1);
    SetTXMaxLen(fcgTXBatBeforeAudioPath,   sizeof(conf->oth.batfile.before_audio) - 1);
    SetTXMaxLen(fcgTXBatAfterAudioPath,    sizeof(conf->oth.batfile.after_audio) - 1);
    SetTXMaxLen(fcgTXBatBeforePath,        sizeof(conf->oth.batfile.before_process) - 1);
    SetTXMaxLen(fcgTXBatAfterPath,         sizeof(conf->oth.batfile.after_process) - 1);

    fcgTSTSettingsNotes->MaxLength     =   sizeof(conf->oth.notes) - 1;
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
    const bool enable_mp4raw_muxer = (0 != str_has_char(sys_dat->exstg->s_mux[MUXER_MP4_RAW].base_cmd));
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

System::Void frmConfig::initUpdater() {
#if ENABLE_AUOSETUP
    frmExeUpdate = gcnew frmUpdate();
    frmExeUpdate->Owner = this;
    frmExeUpdate->init(gcnew svtAV1guiEx::DelegateProcessFin(this, &frmConfig::fcgTSBUpdate_CheckFinished),
                       gcnew svtAV1guiEx::DelegateProcessFin(this, &frmConfig::fcgTSBUpdate_UpdateFinished));
    if (!sys_dat->exstg->s_local.update_check_auto) {
        return;
    }
    if (str_has_char(sys_dat->exstg->s_local.last_update_check)) {
        try {
            DateTime dtLastUpdate = DateTime::Parse(String(sys_dat->exstg->s_local.last_update_check).ToString());
            TimeSpan tsFromLastUpdate = DateTime::Now - dtLastUpdate;
            //一週間以内に確認していれば自動的に更新チェック
            if (tsFromLastUpdate < TimeSpan(7, 0, 0, 0)) {
                return;
            }
        } catch (...) {
            //そのまま下へ
        }
    }
    frmExeUpdate->startCheck();
#else
    fcgTSBUpdate->Enabled = false;
    fcgTSBUpdate->Visible = false;
    toolStripSeparator2->Visible = false;
#endif
}

System::Void frmConfig::InitForm() {
    initUpdater();
    //ローカル設定のロード
    LoadLocalStg();
    //ローカル設定の反映
    SetLocalStg();
    //設定ファイル集の初期化
    InitStgFileList();
    //コンボボックスの値を設定
    InitComboBox();
    //タイムコードのappendix(後付修飾子)を反映
    fcgCBAuoTcfileout->Text = L"タイムコード出力 (" + String(sys_dat->exstg->s_append.tc).ToString() + L")";
    //タイトル表示
    this->Text = String(AUO_FULL_NAME).ToString();
    //バージョン情報,コンパイル日時
    fcgLBVersion->Text     = String(AUO_VERSION_NAME).ToString();
    fcgLBVersionDate->Text = L"build " + String(__DATE__).ToString() + L" " + String(__TIME__).ToString();
    //スレッド数上限
    int max_threads_set = (int)(cpu_core_count() * 1.5 + 0.51);
    fcgNUThreads->Maximum = max_threads_set;
    //ツールチップ
    SetHelpToolTips();
    SetX264VersionToolTip(LocalStg.x264Path);
    ActivateToolTip(sys_dat->exstg->s_local.disable_tooltip_help == FALSE);
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

/////////////         データ <-> GUI     /////////////
System::Void frmConfig::ConfToFrm(CONF_GUIEX *cnf, bool all) {
    //ひたすら書くだけ。めんどい
    CONF_ENCODER enc;
    parse_cmd(&enc, cnf->enc.cmd, true);
    this->SuspendLayout();
    fcgCBUsehighbit->Checked = enc.bit_depth > 8;
    SetCXIndex(fcgCXRC, enc.rc);
    SetCXIndex(fcgCXEncMode, enc.enc_mode);
    SetNUValue(fcgNUQP, enc.qp);
    SetNUValue(fcgNUHierarchicalLevels, enc.hierarchical_levels); //hierarchical-levels
    SetNUValue(fcgNUIntraPeriod, enc.intra_period);        //intra-period
    SetNUValue(fcgNUIntraRefreshType, enc.intra_refresh_type);

    fcgCBUseDefaultMeHme->Checked = enc.use_default_me_hme != 0;  //use-default-me-hme
    fcgCBInLoopMe->Checked = enc.in_loop_me != 0; //in-loop-me
    fcgCBLocalWarp->Checked = enc.local_warp != 0; //local-warp
    fcgCBExtBlock->Checked = enc.ext_block != 0;  //ext-block
    fcgCBSceneChange->Checked = enc.scd != 0;        //scd (scene change detection)
    fcgCBSharp->Checked = enc.sharp != 0;      //improve sharpness
    SetCXIndex(fcgCXSCM, enc.scm);        //scm
    SetCXIndex(fcgCXAQ,  enc.aq);        //aq
    SetNUValue(fcgNUSearchW, enc.search_w);   //search_w
    SetNUValue(fcgNUSearchH, enc.search_h);   //search_h
    SetNUValue(fcgNULookaheadDistance, enc.lad);        //lad (lookahead distance)
    SetNUValue(fcgNUThreads ,enc.lp);         //lp (LogicalProcessorNumber)
    SetNUValue(fcgNUTileRows, enc.tile_rows);   //tile-rows
    SetNUValue(fcgNUTileColumns, enc.tile_columns); //tile-columns

    if (all) {

        fcgCBAFS->Checked                  = cnf->vid.afs != 0;

        SetCXIndex(fcgCXX264Priority,        cnf->vid.priority);
        SetCXIndex(fcgCXTempDir,             cnf->oth.temp_dir);

        fcgTXCmdEx->Text            = String(cnf->vid.cmdex).ToString();

        //音声
        fcgCBAudioOnly->Checked            = cnf->oth.out_audio_only != 0;
        fcgCBFAWCheck->Checked             = cnf->aud.faw_check != 0;
        SetCXIndex(fcgCXAudioEncoder,        cnf->aud.encoder);
        fcgCBAudio2pass->Checked           = cnf->aud.use_2pass != 0;
        fcgCBAudioUsePipe->Checked = (CurrentPipeEnabled && !cnf->aud.use_wav);
        SetCXIndex(fcgCXAudioDelayCut,       cnf->aud.delay_cut);
        SetCXIndex(fcgCXAudioEncMode,        cnf->aud.enc_mode);
        SetNUValue(fcgNUAudioBitrate,       (cnf->aud.bitrate != 0) ? cnf->aud.bitrate : GetCurrentAudioDefaultBitrate());
        SetCXIndex(fcgCXAudioPriority,       cnf->aud.priority);
        SetCXIndex(fcgCXAudioTempDir,        cnf->aud.aud_temp_dir);
        SetCXIndex(fcgCXAudioEncTiming,      cnf->aud.audio_encode_timing);
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
        fcgCBMPGMuxerExt->Checked          = cnf->mux.disable_mpgext == 0;
        SetCXIndex(fcgCXMPGCmdEx,            cnf->mux.mpg_mode);
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
    CONF_ENCODER enc = get_default_prm();
    //x264部
    enc.bit_depth            = fcgCBUsehighbit->Checked ? 10 : 8;
    enc.rc                   = fcgCXRC->SelectedIndex;
    enc.enc_mode             = fcgCXEncMode->SelectedIndex;
    //enc.bitrate              = cnf_fcgTemp->bitrate;
    enc.qp                   = (int)fcgNUQP->Value;

    enc.hierarchical_levels = (int)fcgNUHierarchicalLevels->Value;
    enc.intra_period = (int)fcgNUIntraPeriod->Value;
    enc.intra_refresh_type = (int)fcgNUIntraRefreshType->Value;

    enc.scm = fcgCXSCM->SelectedIndex;
    enc.aq = fcgCXAQ->SelectedIndex;
    enc.search_w = (int)fcgNUSearchW->Value;
    enc.search_h = (int)fcgNUSearchH->Value;
    enc.lad = (int)fcgNULookaheadDistance->Value;
    enc.lp = (int)fcgNUThreads->Value;
    enc.tile_rows = (int)fcgNUTileRows->Value;
    enc.tile_columns = (int)fcgNUTileColumns->Value;

    enc.use_default_me_hme = fcgCBUseDefaultMeHme->Checked;  //use-default-me-hme
    enc.in_loop_me = fcgCBInLoopMe->Checked; //in-loop-me
    enc.local_warp = fcgCBLocalWarp->Checked; //local-warp
    enc.ext_block = fcgCBExtBlock->Checked;  //ext-block
    enc.scd = fcgCBSceneChange->Checked;        //scd (scene change detection)
    enc.sharp = fcgCBSharp->Checked;      //improve sharpness

    //拡張部
    cnf->vid.afs                    = fcgCBAFS->Checked;
    cnf->vid.priority               = fcgCXX264Priority->SelectedIndex;
    cnf->oth.temp_dir               = fcgCXTempDir->SelectedIndex;
    GetCHARfromString(cnf->vid.cmdex, fcgTXCmdEx->Text);

    //音声部
    cnf->aud.encoder                = fcgCXAudioEncoder->SelectedIndex;
    cnf->oth.out_audio_only         = fcgCBAudioOnly->Checked;
    cnf->aud.faw_check              = fcgCBFAWCheck->Checked;
    cnf->aud.enc_mode               = fcgCXAudioEncMode->SelectedIndex;
    cnf->aud.bitrate                = (int)fcgNUAudioBitrate->Value;
    cnf->aud.use_2pass              = fcgCBAudio2pass->Checked;
    cnf->aud.use_wav                = !fcgCBAudioUsePipe->Checked;
    cnf->aud.delay_cut              = fcgCXAudioDelayCut->SelectedIndex;
    cnf->aud.priority               = fcgCXAudioPriority->SelectedIndex;
    cnf->aud.audio_encode_timing    = fcgCXAudioEncTiming->SelectedIndex;
    cnf->aud.aud_temp_dir           = fcgCXAudioTempDir->SelectedIndex;

    //mux部
    cnf->mux.disable_mp4ext         = !fcgCBMP4MuxerExt->Checked;
    cnf->mux.apple_mode             = fcgCBMP4MuxApple->Checked;
    cnf->mux.mp4_mode               = fcgCXMP4CmdEx->SelectedIndex;
    cnf->mux.mp4_temp_dir           = fcgCXMP4BoxTempDir->SelectedIndex;
    cnf->mux.disable_mkvext         = !fcgCBMKVMuxerExt->Checked;
    cnf->mux.mkv_mode               = fcgCXMKVCmdEx->SelectedIndex;
    cnf->mux.disable_mpgext         = !fcgCBMPGMuxerExt->Checked;
    cnf->mux.mpg_mode               = fcgCXMPGCmdEx->SelectedIndex;
    cnf->mux.priority               = fcgCXMuxPriority->SelectedIndex;

    cnf->oth.run_bat                = RUN_BAT_NONE;
    cnf->oth.run_bat               |= (fcgCBRunBatBeforeAudio->Checked) ? RUN_BAT_BEFORE_AUDIO   : NULL;
    cnf->oth.run_bat               |= (fcgCBRunBatAfterAudio->Checked)  ? RUN_BAT_AFTER_AUDIO    : NULL;
    cnf->oth.run_bat               |= (fcgCBRunBatBefore->Checked)      ? RUN_BAT_BEFORE_PROCESS : NULL;
    cnf->oth.run_bat               |= (fcgCBRunBatAfter->Checked)       ? RUN_BAT_AFTER_PROCESS  : NULL;
    cnf->oth.dont_wait_bat_fin      = RUN_BAT_NONE;
    cnf->oth.dont_wait_bat_fin     |= (!fcgCBWaitForBatBefore->Checked) ? RUN_BAT_BEFORE_PROCESS : NULL;
    cnf->oth.dont_wait_bat_fin     |= (!fcgCBWaitForBatAfter->Checked)  ? RUN_BAT_AFTER_PROCESS  : NULL;
    GetCHARfromString(cnf->oth.batfile.before_process, fcgTXBatBeforePath->Text);
    GetCHARfromString(cnf->oth.batfile.after_process,  fcgTXBatAfterPath->Text);
    GetCHARfromString(cnf->oth.batfile.before_audio,   fcgTXBatBeforeAudioPath->Text);
    GetCHARfromString(cnf->oth.batfile.after_audio,    fcgTXBatAfterAudioPath->Text);

    GetfcgTSLSettingsNotes(cnf->oth.notes, sizeof(cnf->oth.notes));
    strcpy_s(cnf->enc.cmd, gen_cmd(&enc, true).c_str());

    //cli mode
    cnf->oth.disable_guicmd         = fcgTSBCMDOnly->Checked;

    return String(gen_cmd(&enc, false).c_str()).ToString();
}

System::Void frmConfig::GetfcgTSLSettingsNotes(char *notes, int nSize) {
    ZeroMemory(notes, nSize);
    if (fcgTSLSettingsNotes->ForeColor == Color::FromArgb(StgNotesColor[0][0], StgNotesColor[0][1], StgNotesColor[0][2]))
        GetCHARfromString(notes, nSize, fcgTSLSettingsNotes->Text);
}

System::Void frmConfig::SetfcgTSLSettingsNotes(const char *notes) {
    if (str_has_char(notes)) {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[0][0], StgNotesColor[0][1], StgNotesColor[0][2]);
        fcgTSLSettingsNotes->Text = String(notes).ToString();
    } else {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[1][0], StgNotesColor[1][1], StgNotesColor[1][2]);
        fcgTSLSettingsNotes->Text = String(DefaultStgNotes).ToString();
    }
}

System::Void frmConfig::SetfcgTSLSettingsNotes(String^ notes) {
    if (notes->Length && String::Compare(notes, String(DefaultStgNotes).ToString()) != 0) {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[0][0], StgNotesColor[0][1], StgNotesColor[0][2]);
        fcgTSLSettingsNotes->Text = notes;
    } else {
        fcgTSLSettingsNotes->ForeColor = Color::FromArgb(StgNotesColor[1][0], StgNotesColor[1][1], StgNotesColor[1][2]);
        fcgTSLSettingsNotes->Text = String(DefaultStgNotes).ToString();
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

//System::Void frmConfig::SetHelpToolTipsColorMatrix(Control^ control, const char *type) {
//    const ENC_OPTION_STR *list = get_option_list(type);
//    fcgTTX264->SetToolTip(control,      L"--" + String(type).ToString() + L"\n"
//        + L"auto とするとAviutlの色空間「自動」に合わせ\n"
//        + L"以下のように設定します。\n"
//        + L"縦解像度" + COLOR_MATRIX_THRESHOLD + L"以上 … " + String(list[COLOR_MATRIX_HD].desc).ToString() + L"\n"
//        + L"縦解像度" + COLOR_MATRIX_THRESHOLD + L"未満 … " + String(list[COLOR_MATRIX_SD].desc).ToString() + L"\n"
//        + L"よくわからない場合は 指定なし が無難です。"
//        );
//}

System::Void frmConfig::SetHelpToolTips() {
    //x264基本
    fcgTTX264->SetToolTip(fcgCBUsehighbit, L""
        + L"--input-depth 16 --output-depth 10\n"
        + L"\n"
        + L"10bit深度でエンコードを行います。\n"
        + L"通常のプレーヤーでは再生できないこともあるため、\n"
        + L"high bit depthエンコードがなにかを理解している場合にのみ、\n"
        + L"使用してください。"
        );
    fcgTTX264->SetToolTip(fcgBTX264Path, L""
        + L"SvtAv1EncApp.exeの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTX264->SetToolTip(fcgBTX264PathSub, L""
        + L"SvtAv1EncApp.exeの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );

    //色空間
    //SetHelpToolTipsColorMatrix(fcgCXColorMatrix, "colormatrix");
    //SetHelpToolTipsColorMatrix(fcgCXColorPrim,   "colorprim");
    //SetHelpToolTipsColorMatrix(fcgCXTransfer,    "transfer");
    //fcgTTX264->SetToolTip(fcgCXInputRange,      L"--input-range\n"
    //    + L"\n"
    //    + L"\"" + String(list_input_range[0].desc).ToString() + L"\"  [デフォルト]\n"
    //    + L"  output-csp yuv系 … tv色調 (圧縮レンジ)\n"
    //    + L"  output-csp rgb系 … pc色調\n"
    //    + L"\n"
    //    + L"\"" + String(list_input_range[1].desc).ToString() + L"\"\n"
    //    + L"  pc色調 (フルレンジ)"
    //    );

    fcgTTX264->SetToolTip(fcgCXAspectRatio,      L""
        + String(aspect_desc[0]).ToString() + L"\n"
        + L"   --sar を直接指定します。\n"
        + L"\n"
        + String(aspect_desc[1]).ToString() + L"\n"
        + L"   エンコード時に 解像度から --sarを自動計算します。"
        );
    fcgTTX264->SetToolTip(fcgNUAspectRatioX,     L"アスペクト比 横 (幅)");
    fcgTTX264->SetToolTip(fcgNUAspectRatioY,     L"アスペクト比 縦 (高さ)");
    fcgTTX264->SetToolTip(fcgNUThreads,          L"--threads\n"
        + L"\"0\" で自動です。"
        );

    //拡張
    fcgTTEx->SetToolTip(fcgCBAFS,                L""
        + L"自動フィールドシフト(afs)を使用してVFR化を行います。\n"
        + L"エンコード時にタイムコードを作成し、mux時に埋め込んで\n"
        + L"フレームレートを変更します。\n"
        + L"\n"
        + L"外部muxerの使用が必須となり、mp4出力時は\n"
        + L"mp4boxとともにtc2mp4modが必要になりますので、\n"
        + L"忘れずに指定してください。\n"
        + L"\n"
        + L"また、あとからフレームレートを変更するため、\n"
        + L"x264のVBV設定が正確に反映されなくなる点に注意してください。"
        );
    fcgTTEx->SetToolTip(fcgCBAFSBitrateCorrection, L""
        + L"自動フィールドシフト(afs)使用時にはmux時のフレームレート変更により\n"
        + L"実レートが指定したビットレートからずれてしまいます。\n"
        + L"\n"
        + L"そこで、1pass目のdrop数から計算して\n"
        + L"ビットレート指定値の補正を行います。\n"
        + L"これにより最終的な実レートが設定通りの動画を作成できます。"
        );
    fcgTTEx->SetToolTip(fcgCBAuoTcfileout, L""
        + L"タイムコードを出力します。このタイムコードは\n"
        + L"自動フィールドシフト(afs)を反映したものになります。"
        );
    fcgTTEx->SetToolTip(fcgCXTempDir,      L""
        + L"一時ファイル群\n"
        + L"・音声一時ファイル(wav / エンコード後音声)\n"
        + L"・動画一時ファイル\n"
        + L"・タイムコードファイル\n"
        + L"・qpファイル\n"
        + L"・mux後ファイル\n"
        + L"の作成場所を指定します。"
        );
    fcgTTEx->SetToolTip(fcgBTCustomTempDir, L""
        + L"一時ファイルの場所を「カスタム」に設定した際に\n"
        + L"使用される一時ファイルの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgBTCmdEx,       L""
        + L"入力したコマンド(オプション)をGUIに反映させます。"
        );

    //音声
    fcgTTEx->SetToolTip(fcgCXAudioEncoder, L""
        + L"使用する音声エンコーダを指定します。\n"
        + L"これらの設定はsvtAV1guiEx.iniに記述されています。"
        );
    fcgTTEx->SetToolTip(fcgCBAudioOnly,    L""
        + L"動画の出力を行わず、音声エンコードのみ行います。\n"
        + L"音声エンコードに失敗した場合などに使用してください。"
        );
    fcgTTEx->SetToolTip(fcgCBFAWCheck,     L""
        + L"音声エンコード時に音声がFakeAACWav(FAW)かどうかの判定を行い、\n"
        + L"FAWだと判定された場合、設定を無視して、\n"
        + L"自動的にFAWを使用するよう切り替えます。\n"
        + L"\n"
        + L"一度音声エンコーダからFAW(fawcl)を選択し、\n"
        + L"実行ファイルの場所を指定しておく必要があります。"
        );
    fcgTTEx->SetToolTip(fcgBTAudioEncoderPath, L""
        + L"音声エンコーダの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgCXAudioEncMode, L""
        + L"音声エンコーダのエンコードモードを切り替えます。\n"
        + L"これらの設定はsvtAV1guiEx.iniに記述されています。"
        );
    fcgTTEx->SetToolTip(fcgCBAudio2pass,   L""
        + L"音声エンコードを2passで行います。\n"
        + L"2pass時はパイプ処理は行えません。"
        );
    fcgTTEx->SetToolTip(fcgCBAudioUsePipe, L""
        + L"パイプを通して、音声データをエンコーダに渡します。\n"
        + L"パイプと2passは同時に指定できません。"
        );
    fcgTTEx->SetToolTip(fcgNUAudioBitrate, L""
        + L"音声ビットレートを指定します。"
        );
    fcgTTEx->SetToolTip(fcgCXAudioPriority, L""
        + L"音声エンコーダのCPU優先度を設定します。\n"
        + L"AviutlSync で Aviutlの優先度と同じになります。"
        );
    fcgTTEx->SetToolTip(fcgCXAudioEncTiming, L""
        + L"音声を処理するタイミングを設定します。\n"
        + L" 後　 … 映像→音声の順で処理します。\n"
        + L" 前　 … 音声→映像の順で処理します。\n"
        + L" 同時 … 映像と音声を同時に処理します。"
        );
    fcgTTEx->SetToolTip(fcgCXAudioTempDir, L""
        + L"音声一時ファイル(エンコード後のファイル)\n"
        + L"の出力先を変更します。"
        );
    fcgTTEx->SetToolTip(fcgBTCustomAudioTempDir, L""
        + L"音声一時ファイルの場所を「カスタム」にした時に\n"
        + L"使用される音声一時ファイルの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    //音声バッチファイル実行
    fcgTTEx->SetToolTip(fcgCBRunBatBeforeAudio, L""
        + L"音声エンコード開始前にバッチファイルを実行します。"
        );
    fcgTTEx->SetToolTip(fcgCBRunBatAfterAudio, L""
        + L"音声エンコード終了後、バッチファイルを実行します。"
        );
    fcgTTEx->SetToolTip(fcgBTBatBeforeAudioPath, L""
        + L"音声エンコード終了後実行するバッチファイルを指定します。\n"
        + L"実際のバッチ実行時には新たに\"<バッチファイル名>_tmp.bat\"を作成、\n"
        + L"指定したバッチファイルの内容をコピーし、\n"
        + L"さらに特定文字列を置換して実行します。\n"
        + L"使用できる置換文字列はreadmeをご覧下さい。"
        );
    fcgTTEx->SetToolTip(fcgBTBatAfterAudioPath, L""
        + L"音声エンコード終了後実行するバッチファイルを指定します。\n"
        + L"実際のバッチ実行時には新たに\"<バッチファイル名>_tmp.bat\"を作成、\n"
        + L"指定したバッチファイルの内容をコピーし、\n"
        + L"さらに特定文字列を置換して実行します。\n"
        + L"使用できる置換文字列はreadmeをご覧下さい。"
        );

    //muxer
    fcgTTEx->SetToolTip(fcgCBMP4MuxerExt, L""
        + L"指定したmuxerでmuxを行います。\n"
        + L"チェックを外すとmuxを行いません。"
        );
    fcgTTEx->SetToolTip(fcgCXMP4CmdEx,    L""
        + L"muxerに渡す追加オプションを選択します。\n"
        + L"これらの設定はsvtAV1guiEx.iniに記述されています。"
        );
    fcgTTEx->SetToolTip(fcgBTMP4MuxerPath, L""
        + L"mp4用muxerの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgBTTC2MP4Path, L""
        + L"tc2mp4modの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgBTMP4RawPath, L""
        + L"raw用mp4muxerの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgCXMP4BoxTempDir, L""
        + L"mp4box用の一時フォルダの場所を指定します。"
        );
    fcgTTEx->SetToolTip(fcgBTMP4BoxTempDir, L""
        + L"mp4box用一時フォルダの場所を「カスタム」に設定した際に\n"
        + L"使用される一時フォルダの場所です。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgCBMKVMuxerExt, L""
        + L"指定したmuxerでmuxを行います。\n"
        + L"チェックを外すとmuxを行いません。"
        );
    fcgTTEx->SetToolTip(fcgCXMKVCmdEx,    L""
        + L"muxerに渡す追加オプションを選択します。\n"
        + L"これらの設定はsvtAV1guiEx.iniに記述されています。"
        );
    fcgTTEx->SetToolTip(fcgBTMKVMuxerPath, L""
        + L"mkv用muxerの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgCBMPGMuxerExt, L""
        + L"指定したmuxerでmuxを行います。\n"
        + L"チェックを外すとmuxを行いません。"
        );
    fcgTTEx->SetToolTip(fcgCXMPGCmdEx,    L""
        + L"muxerに渡す追加オプションを選択します。\n"
        + L"これらの設定はsvtAV1guiEx.iniに記述されています。"
        );
    fcgTTEx->SetToolTip(fcgBTMPGMuxerPath, L""
        + L"mpg用muxerの場所を指定します。\n"
        + L"\n"
        + L"この設定はsvtAV1guiEx.confに保存され、\n"
        + L"バッチ処理ごとの変更はできません。"
        );
    fcgTTEx->SetToolTip(fcgCXMuxPriority, L""
        + L"muxerのCPU優先度を指定します。\n"
        + L"AviutlSync で Aviutlの優先度と同じになります。"
        );
    //バッチファイル実行
    fcgTTEx->SetToolTip(fcgCBRunBatBefore, L""
        + L"エンコード開始前にバッチファイルを実行します。"
        );
    fcgTTEx->SetToolTip(fcgCBRunBatAfter, L""
        + L"エンコード終了後、バッチファイルを実行します。"
        );
    fcgTTEx->SetToolTip(fcgCBWaitForBatBefore, L""
        + L"バッチ処理開始後、バッチ処理が終了するまで待機します。"
        );
    fcgTTEx->SetToolTip(fcgCBWaitForBatAfter, L""
        + L"バッチ処理開始後、バッチ処理が終了するまで待機します。"
        );
    fcgTTEx->SetToolTip(fcgBTBatBeforePath, L""
        + L"エンコード終了後実行するバッチファイルを指定します。\n"
        + L"実際のバッチ実行時には新たに\"<バッチファイル名>_tmp.bat\"を作成、\n"
        + L"指定したバッチファイルの内容をコピーし、\n"
        + L"さらに特定文字列を置換して実行します。\n"
        + L"使用できる置換文字列はreadmeをご覧下さい。"
        );
    fcgTTEx->SetToolTip(fcgBTBatAfterPath, L""
        + L"エンコード終了後実行するバッチファイルを指定します。\n"
        + L"実際のバッチ実行時には新たに\"<バッチファイル名>_tmp.bat\"を作成、\n"
        + L"指定したバッチファイルの内容をコピーし、\n"
        + L"さらに特定文字列を置換して実行します。\n"
        + L"使用できる置換文字列はreadmeをご覧下さい。"
        );
    //上部ツールストリップ
    fcgTSBCMDOnly->ToolTipText = L""
        + L"GUIモード と CLIモードを切り替えます。\n"
        + L"CLIモードはコマンドライン入力のみで\n"
        + L"オプションの指定を行います。";

    fcgTSBDelete->ToolTipText = L""
        + L"現在選択中のプロファイルを削除します。";

    fcgTSBOtherSettings->ToolTipText = L""
        + L"プロファイルの保存フォルダを変更します。";

    fcgTSBSave->ToolTipText = L""
        + L"現在の設定をプロファイルに上書き保存します。";

    fcgTSBSaveNew->ToolTipText = L""
        + L"現在の設定を新たなプロファイルに保存します。";

    //他
    fcgTTEx->SetToolTip(fcgTXCmd,         L""
        + L"x264に渡される予定のコマンドラインです。\n"
        + L"エンコード時には更に\n"
        + L"・「追加コマンド」の付加\n"
        + L"・\"auto\"な設定項目の反映\n"
        + L"・必要な情報の付加(--fps/-o/--input-res/--input-csp/--frames等)\n"
        + L"が行われます。\n"
        + L"\n"
        + L"このウィンドウはダブルクリックで拡大縮小できます。"
        );
    fcgTTEx->SetToolTip(fcgBTDefault,     L""
        + L"デフォルト設定をロードします。"
        );
}
System::Void frmConfig::SetX264VersionToolTip(String^ x264Path) {
    String^ mes;
    if (File::Exists(x264Path)) {
        char mes_buf[2560];
        char exe_path[MAX_PATH_LEN];
        GetCHARfromString(exe_path, sizeof(exe_path), x264Path);
        if (get_exe_message(exe_path, "--version", mes_buf, _countof(mes_buf), AUO_PIPE_MUXED) == RP_SUCCESS)
            mes = String(mes_buf).ToString();
        else
            mes = L"バージョン情報の取得に失敗しました。";
    } else {
        mes = L"指定されたx264が存在しません。";
    }
    fcgTTX264Version->SetToolTip(fcgTXX264Path, mes);
    fcgTTX264Version->SetToolTip(fcgTXX264PathSub, mes);
}
System::Void frmConfig::ShowExehelp(String^ ExePath, String^ args) {
    if (!File::Exists(ExePath)) {
        MessageBox::Show(L"指定された実行ファイルが存在しません。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
    } else {
        char exe_path[MAX_PATH_LEN];
        char file_path[MAX_PATH_LEN];
        char cmd[MAX_CMD_LEN];
        GetCHARfromString(exe_path, sizeof(exe_path), ExePath);
        apply_appendix(file_path, _countof(file_path), exe_path, "_fullhelp.txt");
        File::Delete(String(file_path).ToString());
        array<String^>^ arg_list = args->Split(L';');
        for (int i = 0; i < arg_list->Length; i++) {
            if (i) {
                StreamWriter^ sw;
                try {
                    sw = gcnew StreamWriter(String(file_path).ToString(), true, System::Text::Encoding::GetEncoding("shift_jis"));
                    sw->WriteLine();
                    sw->WriteLine();
                } finally {
                    if (sw != nullptr) { sw->Close(); }
                }
            }
            GetCHARfromString(cmd, sizeof(cmd), arg_list[i]);
            if (get_exe_message_to_file(exe_path, cmd, file_path, AUO_PIPE_MUXED, 5) != RP_SUCCESS) {
                File::Delete(String(file_path).ToString());
                MessageBox::Show(L"helpの取得に失敗しました。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
        }
        try {
            System::Diagnostics::Process::Start(String(file_path).ToString());
        } catch (...) {
            MessageBox::Show(L"helpを開く際に不明なエラーが発生しました。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}

#pragma warning( pop )
