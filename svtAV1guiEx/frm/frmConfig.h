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

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "auo.h"
#include "auo_pipe.h"
#include "auo_conf.h"
#include "auo_settings.h"
#include "auo_system.h"
#include "auo_util.h"
#include "auo_clrutil.h"

#include "h264_level.h"
#include "transparentLabel.h"

#include "frmConfig_helper.h"
#include "auo_mes.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


namespace AUO_NAME_R {

    /// <summary>
    /// frmConfig の概要
    ///
    /// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
    ///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
    ///          変更する必要があります。この変更を行わないと、
    ///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
    ///          正しく相互に利用できなくなります。
    /// </summary>
    public ref class frmConfig : public System::Windows::Forms::Form
    {
    public:
        frmConfig(CONF_GUIEX *_conf, const SYSTEM_DATA *_sys_dat)
        {
            InitData(_conf, _sys_dat);
            list_lng = nullptr;
            dwStgReader = nullptr;
            themeMode = AuoTheme::DefaultLight;
            cnf_stgSelected = (CONF_GUIEX*)calloc(1, sizeof(CONF_GUIEX));
            InitializeComponent();
            //
            //TODO: ここにコンストラクタ コードを追加します
            //
            fcgLastX264ModeAsAMP = true;
            LoadLangText();
        }

    protected:
        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        ~frmConfig()
        {
            if (components)
            {
                delete components;
            }
            CloseBitrateCalc();
            if (cnf_stgSelected) free(cnf_stgSelected); cnf_stgSelected = NULL;
            if (dwStgReader != nullptr)
                delete dwStgReader;
            if (qualityTimer != nullptr)
                delete qualityTimer;
            if (list_lng != nullptr)
                delete list_lng;
        }
private: System::Windows::Forms::Label^  fcgLBAMPAutoBitrate;


    private: System::Windows::Forms::TabControl^  fcgtabControlVideo;
    private: System::Windows::Forms::TabPage ^fcgtabPageSVTAV1_1;



    private: System::Windows::Forms::ToolStrip^  fcgtoolStripSettings;

    private: System::Windows::Forms::TabControl^  fcgtabControlMux;


    private: System::Windows::Forms::TabPage^  fcgtabPageMP4;
    private: System::Windows::Forms::TabPage^  fcgtabPageMKV;
    private: System::Windows::Forms::TextBox^  fcgTXCmd;

    private: System::Windows::Forms::Button^  fcgBTCancel;

    private: System::Windows::Forms::Button^  fcgBTOK;
    private: System::Windows::Forms::Button^  fcgBTDefault;



    private: System::Windows::Forms::TabPage^  fcgtabPageExSettings;
    private: System::Windows::Forms::ToolStripButton^  fcgTSBSave;

    private: System::Windows::Forms::ToolStripButton^  fcgTSBSaveNew;

    private: System::Windows::Forms::ToolStripButton^  fcgTSBDelete;

    private: System::Windows::Forms::ToolStripSeparator^  fcgtoolStripSeparator1;
    private: System::Windows::Forms::ToolStripDropDownButton^  fcgTSSettings;

    private: System::Windows::Forms::ToolStripButton^  fcgTSBCMDOnly;
    private: System::Windows::Forms::TextBox^  fcgTXX264Path;
    private: System::Windows::Forms::Label^  fcgLBX264Path;





    private: System::Windows::Forms::ComboBox^  fcgCXRC;
    private: System::Windows::Forms::CheckBox^  fcgCBUsehighbit;

    private: System::Windows::Forms::Button^  fcgBTX264Path;




















































































































































































































    private: System::Windows::Forms::GroupBox^  fcggroupBoxExSettings;
    private: System::Windows::Forms::CheckBox^  fcgCBAFSBitrateCorrection;


    private: System::Windows::Forms::CheckBox^  fcgCBAFS;
    private: System::Windows::Forms::Label^  fcgLBX264Priority;


    private: System::Windows::Forms::CheckBox^  fcgCBAuoTcfileout;

    private: System::Windows::Forms::Button^  fcgBTCustomTempDir;
    private: System::Windows::Forms::TextBox^  fcgTXCustomTempDir;
    private: System::Windows::Forms::ComboBox^  fcgCXTempDir;
    private: System::Windows::Forms::ComboBox^  fcgCXX264Priority;
    private: System::Windows::Forms::GroupBox^  fcggroupBoxCmdEx;
    private: System::Windows::Forms::Button^  fcgBTCmdEx;
    private: System::Windows::Forms::TextBox^  fcgTXCmdEx;











    private: System::Windows::Forms::TabPage^  fcgtabPageMux;










    private: System::Windows::Forms::Label^  fcgLBMaxTXSize;
    private: System::Windows::Forms::ComboBox^  fcgCXMaxTXSize;

    private: System::Windows::Forms::ComboBox^  fcgCXMP4CmdEx;

    private: System::Windows::Forms::Label^  fcgLBMP4CmdEx;
    private: System::Windows::Forms::CheckBox^  fcgCBMP4MuxerExt;
    private: System::Windows::Forms::Button^  fcgBTMP4BoxTempDir;
    private: System::Windows::Forms::TextBox^  fcgTXMP4BoxTempDir;


    private: System::Windows::Forms::ComboBox^  fcgCXMP4BoxTempDir;
    private: System::Windows::Forms::Label^  fcgLBMP4BoxTempDir;
    private: System::Windows::Forms::Button^  fcgBTTC2MP4Path;
    private: System::Windows::Forms::TextBox^  fcgTXTC2MP4Path;
    private: System::Windows::Forms::Button^  fcgBTMP4MuxerPath;
    private: System::Windows::Forms::TextBox^  fcgTXMP4MuxerPath;

    private: System::Windows::Forms::Label^  fcgLBTC2MP4Path;
    private: System::Windows::Forms::Label^  fcgLBMP4MuxerPath;


    private: System::Windows::Forms::Button^  fcgBTMKVMuxerPath;

    private: System::Windows::Forms::TextBox^  fcgTXMKVMuxerPath;

    private: System::Windows::Forms::Label^  fcgLBMKVMuxerPath;
    private: System::Windows::Forms::ComboBox^  fcgCXMKVCmdEx;
    private: System::Windows::Forms::Label^  fcgLBMKVMuxerCmdEx;
    private: System::Windows::Forms::CheckBox^  fcgCBMKVMuxerExt;
    private: System::Windows::Forms::ComboBox^  fcgCXMuxPriority;
    private: System::Windows::Forms::Label^  fcgLBMuxPriority;

    private: System::Windows::Forms::Label^  fcgLBVersionDate;


    private: System::Windows::Forms::Label^  fcgLBVersion;
    private: System::Windows::Forms::FolderBrowserDialog^  fcgfolderBrowserTemp;
    private: System::Windows::Forms::OpenFileDialog^  fcgOpenFileDialog;









private: System::Windows::Forms::ToolTip^  fcgTTX264;
private: System::Windows::Forms::ToolTip^  fcgTTEx;





private: System::Windows::Forms::ToolTip^  fcgTTX264Version;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
private: System::Windows::Forms::ToolStripButton^  fcgTSBOtherSettings;
private: System::Windows::Forms::CheckBox^  fcgCBNulOutCLI;








































































































private: System::Windows::Forms::Label^  fcgLBTempDir;





private: System::Windows::Forms::ToolStripButton^  fcgTSBBitrateCalc;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
private: System::Windows::Forms::Button^  fcgBTX264PathSub;

private: System::Windows::Forms::TextBox^  fcgTXX264PathSub;

private: System::Windows::Forms::Label^  fcgLBX264PathSub;




private: System::Windows::Forms::ToolStripTextBox^  fcgTSTSettingsNotes;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
private: System::Windows::Forms::ToolStripLabel^  fcgTSLSettingsNotes;
private: System::Windows::Forms::CheckBox^  fcgCBMP4MuxApple;


private: System::Windows::Forms::TabPage^  fcgtabPageBat;
private: System::Windows::Forms::CheckBox^  fcgCBRunBatBefore;
private: System::Windows::Forms::Label^  fcgLBBatBeforePath;



private: System::Windows::Forms::CheckBox^  fcgCBWaitForBatBefore;
private: System::Windows::Forms::Button^  fcgBTBatBeforePath;


private: System::Windows::Forms::TextBox^  fcgTXBatBeforePath;




private: System::Windows::Forms::ContextMenuStrip^  fcgCSReplaceStrings;
























private: System::Windows::Forms::Button^  fcgBTMP4RawPath;

private: System::Windows::Forms::TextBox^  fcgTXMP4RawPath;
private: System::Windows::Forms::Label^  fcgLBMP4RawPath;
private: System::Windows::Forms::ContextMenuStrip^  fcgCSExeFiles;
private: System::Windows::Forms::ToolStripMenuItem^  fcgTSExeFileshelp;


private: System::Windows::Forms::ComboBox^  fcgCXCmdExInsert;
private: System::Windows::Forms::LinkLabel^  fcgLBguiExBlog;
private: System::Windows::Forms::Panel^  fcgPNSeparator;
private: System::Windows::Forms::Button^  fcgBTBatAfterPath;


private: System::Windows::Forms::TextBox^  fcgTXBatAfterPath;

private: System::Windows::Forms::Label^  fcgLBBatAfterPath;

private: System::Windows::Forms::CheckBox^  fcgCBWaitForBatAfter;

private: System::Windows::Forms::CheckBox^  fcgCBRunBatAfter;
private: System::Windows::Forms::Label^  fcgLBBatAfterString;

private: System::Windows::Forms::Label^  fcgLBBatBeforeString;


private: System::Windows::Forms::TabControl^  fcgtabControlAudio;
private: System::Windows::Forms::TabPage^  fcgtabPageAudioMain;
private: System::Windows::Forms::ComboBox^  fcgCXAudioDelayCut;
private: System::Windows::Forms::Label^  fcgLBAudioDelayCut;
private: System::Windows::Forms::Label^  fcgCBAudioEncTiming;
private: System::Windows::Forms::ComboBox^  fcgCXAudioEncTiming;
private: System::Windows::Forms::ComboBox^  fcgCXAudioTempDir;
private: System::Windows::Forms::TextBox^  fcgTXCustomAudioTempDir;
private: System::Windows::Forms::Button^  fcgBTCustomAudioTempDir;
private: System::Windows::Forms::CheckBox^  fcgCBAudioUsePipe;
private: System::Windows::Forms::Label^  fcgLBAudioBitrate;
private: System::Windows::Forms::NumericUpDown^  fcgNUAudioBitrate;
private: System::Windows::Forms::CheckBox^  fcgCBAudio2pass;
private: System::Windows::Forms::ComboBox^  fcgCXAudioEncMode;
private: System::Windows::Forms::Label^  fcgLBAudioEncMode;
private: System::Windows::Forms::Button^  fcgBTAudioEncoderPath;
private: System::Windows::Forms::TextBox^  fcgTXAudioEncoderPath;
private: System::Windows::Forms::Label^  fcgLBAudioEncoderPath;
private: System::Windows::Forms::CheckBox^  fcgCBAudioOnly;
private: System::Windows::Forms::CheckBox^  fcgCBFAWCheck;
private: System::Windows::Forms::ComboBox^  fcgCXAudioEncoder;
private: System::Windows::Forms::Label^  fcgLBAudioEncoder;
private: System::Windows::Forms::Label^  fcgLBAudioTemp;
private: System::Windows::Forms::TabPage^  fcgtabPageAudioOther;
private: System::Windows::Forms::Panel^  panel2;
private: System::Windows::Forms::Label^  fcgLBBatAfterAudioString;

private: System::Windows::Forms::Label^  fcgLBBatBeforeAudioString;
private: System::Windows::Forms::Button^  fcgBTBatAfterAudioPath;


private: System::Windows::Forms::TextBox^  fcgTXBatAfterAudioPath;

private: System::Windows::Forms::Label^  fcgLBBatAfterAudioPath;

private: System::Windows::Forms::CheckBox^  fcgCBRunBatAfterAudio;

private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::Button^  fcgBTBatBeforeAudioPath;

private: System::Windows::Forms::TextBox^  fcgTXBatBeforeAudioPath;

private: System::Windows::Forms::Label^  fcgLBBatBeforeAudioPath;

private: System::Windows::Forms::CheckBox^  fcgCBRunBatBeforeAudio;

private: System::Windows::Forms::ComboBox^  fcgCXAudioPriority;
private: System::Windows::Forms::Label^  fcgLBAudioPriority;


private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;


private: System::Windows::Forms::Label ^fcgLBThreads;
private: System::Windows::Forms::NumericUpDown ^fcgNUThreads;


private: System::Windows::Forms::Label ^fcgLBIntraRefreshType;
private: System::Windows::Forms::NumericUpDown ^fcgNUIntraRefreshType;
private: System::Windows::Forms::Label ^fcgLBKeyint;
private: System::Windows::Forms::NumericUpDown ^fcgNUKeyint;


































private: System::Windows::Forms::Label ^fcgLBTile2;



private: System::Windows::Forms::NumericUpDown ^fcgNUTileColumns;
private: System::Windows::Forms::Label ^fcgLBTile;
private: System::Windows::Forms::NumericUpDown ^fcgNUTileRows;
private: System::Windows::Forms::Panel ^fcgPNX264Mode;
private: System::Windows::Forms::NumericUpDown ^fcgNUQP;
private: System::Windows::Forms::ComboBox ^fcgCXEncMode;
private: System::Windows::Forms::NumericUpDown ^fcgNUBitrate;
private: System::Windows::Forms::Label ^fcgLBHierarchicalLevels;


private: System::Windows::Forms::Label ^fcgLBAQ;
private: System::Windows::Forms::ComboBox ^fcgCXAQ;

private: System::Windows::Forms::Label ^fcgLBRC;
private: System::Windows::Forms::Label ^fcgLBEncMode;
private: System::Windows::Forms::Label ^fcgLBKbps;












private: System::Windows::Forms::ComboBox ^fcgCXEnableMfmv;



private: System::Windows::Forms::Label ^fcgLBMfmv;



















































private: System::Windows::Forms::TabPage ^fcgtabPageSVTAV1_2;






































































private: System::Windows::Forms::Label ^fcgLBMaxQP;
private: System::Windows::Forms::NumericUpDown ^fcgNUMaxQP;
private: System::Windows::Forms::Label ^fcgLBMinQP;
private: System::Windows::Forms::NumericUpDown ^fcgNUMinQP;




































































private: System::Windows::Forms::Label ^fcgLB2pasAuto;
private: System::Windows::Forms::CheckBox ^fcgCB2PassAuto;
private: System::Windows::Forms::ComboBox ^fcgCXProfileAV1;
private: System::Windows::Forms::Label ^fcgLBProfileAV1;


private: System::Windows::Forms::ComboBox ^fcgCXColorFormat;

private: System::Windows::Forms::Label ^fcgLBColorFormat;





















private: System::Windows::Forms::ComboBox ^fcgCXHierarchicalLevels;
private: System::Windows::Forms::GroupBox^  fcgGroupBoxAspectRatio;



private: System::Windows::Forms::NumericUpDown^  fcgNUAspectRatioY;
private: System::Windows::Forms::Label^  fcgLBAspectRatio;
private: System::Windows::Forms::NumericUpDown^  fcgNUAspectRatioX;
private: System::Windows::Forms::ComboBox^  fcgCXAspectRatio;






















































private: System::Windows::Forms::GroupBox^  fcggroupBoxColorMatrix;
private: System::Windows::Forms::ComboBox^  fcgCXColorRange;

private: System::Windows::Forms::Label^  fcgLBInputRange;
private: System::Windows::Forms::ComboBox^  fcgCXTransfer;
private: System::Windows::Forms::ComboBox^  fcgCXColorPrim;
private: System::Windows::Forms::ComboBox^  fcgCXColorMatrix;
private: System::Windows::Forms::Label^  fcgLBTransfer;
private: System::Windows::Forms::Label^  fcgLBColorPrim;
private: System::Windows::Forms::Label^  fcgLBColorMatrix;
private: System::Windows::Forms::Label^  fcgLBSceneChangeDetection;
private: System::Windows::Forms::CheckBox^  fcgCBSceneChangeDetection;





private: System::Windows::Forms::Label^  fcgLBEnableDLF;
private: System::Windows::Forms::CheckBox^  fcgCBEnableDLF;





private: System::Windows::Forms::Label^  fcgLBEnableTF;
private: System::Windows::Forms::CheckBox^  fcgCBEnableOverlay;
private: System::Windows::Forms::Label^  fcgLBEnableOverlay;


private: System::Windows::Forms::CheckBox^  fcgCBEnableCDEF;
private: System::Windows::Forms::Label^  fcgLBEnableCDEF;
private: System::Windows::Forms::Label^  fcgLBFilmGrain;
private: System::Windows::Forms::NumericUpDown^  fcgNUFilmGrain;
private: System::Windows::Forms::ComboBox^  fcgCXSCM;
private: System::Windows::Forms::Label^  fcgLBScm;


private: System::Windows::Forms::Label^  fcgLBOverShootPct;
private: System::Windows::Forms::NumericUpDown^  fcgNUOverShootPct;
private: System::Windows::Forms::Label^  fcgLBUnderShootPct;
private: System::Windows::Forms::NumericUpDown^  fcgNUUnderShootPct;
private: System::Windows::Forms::Label^  fcgLBMaxSectionPct;
private: System::Windows::Forms::NumericUpDown^  fcgNUMaxSectionPct;
private: System::Windows::Forms::Label^  fcgLBMinSectionPct;
private: System::Windows::Forms::NumericUpDown^  fcgNUMinSectionPct;
private: System::Windows::Forms::Label^  fcgLBEnableStatReport;
private: System::Windows::Forms::CheckBox^  fcgCBEnableStatReport;
private: System::Windows::Forms::Label^  fcgLBSTATUS;
private: System::Windows::Forms::TextBox^  fcgTXStatusFile;
private: System::Windows::Forms::Button^  fcgBTStatusFile;
private: System::Windows::Forms::Label^  fcgLBTune;
private: System::Windows::Forms::ComboBox^  fcgCXTune;
private: System::Windows::Forms::Label^  fcgLBFastDecode;
private: System::Windows::Forms::CheckBox^  fcgCBFastDecode;
private: System::Windows::Forms::Panel^  fcgPNHideTabControlVideo;
private: System::Windows::Forms::Panel^  fcgPNHideTabControlAudio;
private: System::Windows::Forms::Panel^  fcgPNHideTabControlMux;
private: System::Windows::Forms::Panel^  fcgPNHideToolStripBorder;
private: System::Windows::Forms::ToolStripDropDownButton^  fcgTSLanguage;
private: System::Windows::Forms::Label^  fcgLBLookahead;
private: System::Windows::Forms::NumericUpDown^  fcgNULookahead;
private: System::Windows::Forms::NumericUpDown^  fcgNUVarianceBoostStrength;





private: System::Windows::Forms::Label^  fcgLBEnableVarianceBoost;
private: System::Windows::Forms::NumericUpDown^  fcgNUSharpness;


private: System::Windows::Forms::Label^  fcgLBVarianceOctile;
private: System::Windows::Forms::NumericUpDown^  fcgNUVarianceOctile;
private: System::Windows::Forms::Label^  fcgLBSharpness;


private: System::Windows::Forms::NumericUpDown^  fcgNULumaQPBias;
private: System::Windows::Forms::Label^  fcgLBLumaQPBias;


private: System::Windows::Forms::CheckBox^  fcgCBEnableRestorationFilter;
private: System::Windows::Forms::Label^  fcgLBEnableRestortionFiltering;
private: System::Windows::Forms::NumericUpDown^  fcgNUTFStrength;
private: System::Windows::Forms::Label^  fcgLBTFStrength;
private: System::Windows::Forms::NumericUpDown^  fcgNUEnableTF;












































































































    private: System::ComponentModel::IContainer^  components;




    private:
        /// <summary>
        /// 必要なデザイナ変数です。
        /// </summary>


#pragma region Windows Form Designer generated code
        /// <summary>
        /// デザイナ サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディタで変更しないでください。
        /// </summary>
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmConfig::typeid));
            this->fcgtabControlVideo = (gcnew System::Windows::Forms::TabControl());
            this->fcgtabPageSVTAV1_1 = (gcnew System::Windows::Forms::TabPage());
            this->fcgNUEnableTF = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgNUTFStrength = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBTFStrength = (gcnew System::Windows::Forms::Label());
            this->fcgNUVarianceOctile = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBSharpness = (gcnew System::Windows::Forms::Label());
            this->fcgNULumaQPBias = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBLumaQPBias = (gcnew System::Windows::Forms::Label());
            this->fcgNUSharpness = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBVarianceOctile = (gcnew System::Windows::Forms::Label());
            this->fcgNUVarianceBoostStrength = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBEnableVarianceBoost = (gcnew System::Windows::Forms::Label());
            this->fcgLBLookahead = (gcnew System::Windows::Forms::Label());
            this->fcgNULookahead = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBFastDecode = (gcnew System::Windows::Forms::Label());
            this->fcgCBFastDecode = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBTune = (gcnew System::Windows::Forms::Label());
            this->fcgCXTune = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBOverShootPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUOverShootPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBUnderShootPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUUnderShootPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMaxSectionPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUMaxSectionPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMinSectionPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUMinSectionPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXMaxTXSize = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMaxTXSize = (gcnew System::Windows::Forms::Label());
            this->fcgCXSCM = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBScm = (gcnew System::Windows::Forms::Label());
            this->fcgCBEnableCDEF = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBEnableCDEF = (gcnew System::Windows::Forms::Label());
            this->fcgLBFilmGrain = (gcnew System::Windows::Forms::Label());
            this->fcgNUFilmGrain = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBEnableTF = (gcnew System::Windows::Forms::Label());
            this->fcgCBEnableOverlay = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBEnableOverlay = (gcnew System::Windows::Forms::Label());
            this->fcgCBEnableDLF = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBEnableDLF = (gcnew System::Windows::Forms::Label());
            this->fcgCBEnableRestorationFilter = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBSceneChangeDetection = (gcnew System::Windows::Forms::Label());
            this->fcgCBSceneChangeDetection = (gcnew System::Windows::Forms::CheckBox());
            this->fcggroupBoxColorMatrix = (gcnew System::Windows::Forms::GroupBox());
            this->fcgCXColorRange = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBInputRange = (gcnew System::Windows::Forms::Label());
            this->fcgCXTransfer = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXColorPrim = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXColorMatrix = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBTransfer = (gcnew System::Windows::Forms::Label());
            this->fcgLBColorPrim = (gcnew System::Windows::Forms::Label());
            this->fcgLBColorMatrix = (gcnew System::Windows::Forms::Label());
            this->fcgGroupBoxAspectRatio = (gcnew System::Windows::Forms::GroupBox());
            this->fcgNUAspectRatioY = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBAspectRatio = (gcnew System::Windows::Forms::Label());
            this->fcgNUAspectRatioX = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXAspectRatio = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXHierarchicalLevels = (gcnew System::Windows::Forms::ComboBox());
            this->fcgPNX264Mode = (gcnew System::Windows::Forms::Panel());
            this->fcgLBKbps = (gcnew System::Windows::Forms::Label());
            this->fcgLBRC = (gcnew System::Windows::Forms::Label());
            this->fcgLBEncMode = (gcnew System::Windows::Forms::Label());
            this->fcgNUBitrate = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXEncMode = (gcnew System::Windows::Forms::ComboBox());
            this->fcgNUQP = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXRC = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLB2pasAuto = (gcnew System::Windows::Forms::Label());
            this->fcgCB2PassAuto = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCXProfileAV1 = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBProfileAV1 = (gcnew System::Windows::Forms::Label());
            this->fcgCXColorFormat = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBColorFormat = (gcnew System::Windows::Forms::Label());
            this->fcgLBEnableRestortionFiltering = (gcnew System::Windows::Forms::Label());
            this->fcgLBMaxQP = (gcnew System::Windows::Forms::Label());
            this->fcgNUMaxQP = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMinQP = (gcnew System::Windows::Forms::Label());
            this->fcgNUMinQP = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXEnableMfmv = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMfmv = (gcnew System::Windows::Forms::Label());
            this->fcgLBAQ = (gcnew System::Windows::Forms::Label());
            this->fcgCXAQ = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBHierarchicalLevels = (gcnew System::Windows::Forms::Label());
            this->fcgLBTile2 = (gcnew System::Windows::Forms::Label());
            this->fcgNUTileColumns = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBTile = (gcnew System::Windows::Forms::Label());
            this->fcgNUTileRows = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBIntraRefreshType = (gcnew System::Windows::Forms::Label());
            this->fcgNUIntraRefreshType = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBKeyint = (gcnew System::Windows::Forms::Label());
            this->fcgNUKeyint = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBThreads = (gcnew System::Windows::Forms::Label());
            this->fcgNUThreads = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCBUsehighbit = (gcnew System::Windows::Forms::CheckBox());
            this->fcgBTX264Path = (gcnew System::Windows::Forms::Button());
            this->fcgTXX264Path = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBX264Path = (gcnew System::Windows::Forms::Label());
            this->fcgtabPageSVTAV1_2 = (gcnew System::Windows::Forms::TabPage());
            this->fcgLBEnableStatReport = (gcnew System::Windows::Forms::Label());
            this->fcgCBEnableStatReport = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBSTATUS = (gcnew System::Windows::Forms::Label());
            this->fcgTXStatusFile = (gcnew System::Windows::Forms::TextBox());
            this->fcgBTStatusFile = (gcnew System::Windows::Forms::Button());
            this->fcgtabPageExSettings = (gcnew System::Windows::Forms::TabPage());
            this->fcgBTX264PathSub = (gcnew System::Windows::Forms::Button());
            this->fcgTXX264PathSub = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBX264PathSub = (gcnew System::Windows::Forms::Label());
            this->fcgLBTempDir = (gcnew System::Windows::Forms::Label());
            this->fcgBTCustomTempDir = (gcnew System::Windows::Forms::Button());
            this->fcggroupBoxCmdEx = (gcnew System::Windows::Forms::GroupBox());
            this->fcgCXCmdExInsert = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCBNulOutCLI = (gcnew System::Windows::Forms::CheckBox());
            this->fcgBTCmdEx = (gcnew System::Windows::Forms::Button());
            this->fcgTXCmdEx = (gcnew System::Windows::Forms::TextBox());
            this->fcgTXCustomTempDir = (gcnew System::Windows::Forms::TextBox());
            this->fcgCXTempDir = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXX264Priority = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBX264Priority = (gcnew System::Windows::Forms::Label());
            this->fcggroupBoxExSettings = (gcnew System::Windows::Forms::GroupBox());
            this->fcgCBAuoTcfileout = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCBAFSBitrateCorrection = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCBAFS = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCSExeFiles = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->fcgTSExeFileshelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->fcgtoolStripSettings = (gcnew System::Windows::Forms::ToolStrip());
            this->fcgTSBSave = (gcnew System::Windows::Forms::ToolStripButton());
            this->fcgTSBSaveNew = (gcnew System::Windows::Forms::ToolStripButton());
            this->fcgTSBDelete = (gcnew System::Windows::Forms::ToolStripButton());
            this->fcgtoolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->fcgTSSettings = (gcnew System::Windows::Forms::ToolStripDropDownButton());
            this->fcgTSBCMDOnly = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->fcgTSLanguage = (gcnew System::Windows::Forms::ToolStripDropDownButton());
            this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->fcgTSBBitrateCalc = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->fcgTSBOtherSettings = (gcnew System::Windows::Forms::ToolStripButton());
            this->fcgTSLSettingsNotes = (gcnew System::Windows::Forms::ToolStripLabel());
            this->fcgTSTSettingsNotes = (gcnew System::Windows::Forms::ToolStripTextBox());
            this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->fcgtabControlMux = (gcnew System::Windows::Forms::TabControl());
            this->fcgtabPageMP4 = (gcnew System::Windows::Forms::TabPage());
            this->fcgCBMP4MuxApple = (gcnew System::Windows::Forms::CheckBox());
            this->fcgBTTC2MP4Path = (gcnew System::Windows::Forms::Button());
            this->fcgTXTC2MP4Path = (gcnew System::Windows::Forms::TextBox());
            this->fcgBTMP4MuxerPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXMP4MuxerPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBTC2MP4Path = (gcnew System::Windows::Forms::Label());
            this->fcgLBMP4MuxerPath = (gcnew System::Windows::Forms::Label());
            this->fcgCXMP4CmdEx = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMP4CmdEx = (gcnew System::Windows::Forms::Label());
            this->fcgCBMP4MuxerExt = (gcnew System::Windows::Forms::CheckBox());
            this->fcgBTMP4RawPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXMP4RawPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBMP4RawPath = (gcnew System::Windows::Forms::Label());
            this->fcgBTMP4BoxTempDir = (gcnew System::Windows::Forms::Button());
            this->fcgTXMP4BoxTempDir = (gcnew System::Windows::Forms::TextBox());
            this->fcgCXMP4BoxTempDir = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMP4BoxTempDir = (gcnew System::Windows::Forms::Label());
            this->fcgtabPageMKV = (gcnew System::Windows::Forms::TabPage());
            this->fcgBTMKVMuxerPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXMKVMuxerPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBMKVMuxerPath = (gcnew System::Windows::Forms::Label());
            this->fcgCXMKVCmdEx = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMKVMuxerCmdEx = (gcnew System::Windows::Forms::Label());
            this->fcgCBMKVMuxerExt = (gcnew System::Windows::Forms::CheckBox());
            this->fcgtabPageMux = (gcnew System::Windows::Forms::TabPage());
            this->fcgCXMuxPriority = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMuxPriority = (gcnew System::Windows::Forms::Label());
            this->fcgtabPageBat = (gcnew System::Windows::Forms::TabPage());
            this->fcgLBBatAfterString = (gcnew System::Windows::Forms::Label());
            this->fcgLBBatBeforeString = (gcnew System::Windows::Forms::Label());
            this->fcgBTBatAfterPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXBatAfterPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBBatAfterPath = (gcnew System::Windows::Forms::Label());
            this->fcgCBWaitForBatAfter = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCBRunBatAfter = (gcnew System::Windows::Forms::CheckBox());
            this->fcgPNSeparator = (gcnew System::Windows::Forms::Panel());
            this->fcgBTBatBeforePath = (gcnew System::Windows::Forms::Button());
            this->fcgTXBatBeforePath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBBatBeforePath = (gcnew System::Windows::Forms::Label());
            this->fcgCBWaitForBatBefore = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCBRunBatBefore = (gcnew System::Windows::Forms::CheckBox());
            this->fcgTXCmd = (gcnew System::Windows::Forms::TextBox());
            this->fcgBTCancel = (gcnew System::Windows::Forms::Button());
            this->fcgBTOK = (gcnew System::Windows::Forms::Button());
            this->fcgBTDefault = (gcnew System::Windows::Forms::Button());
            this->fcgLBVersionDate = (gcnew System::Windows::Forms::Label());
            this->fcgLBVersion = (gcnew System::Windows::Forms::Label());
            this->fcgfolderBrowserTemp = (gcnew System::Windows::Forms::FolderBrowserDialog());
            this->fcgOpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
            this->fcgTTX264 = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->fcgTTEx = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->fcgTTX264Version = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->fcgCSReplaceStrings = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
            this->fcgLBguiExBlog = (gcnew System::Windows::Forms::LinkLabel());
            this->fcgtabControlAudio = (gcnew System::Windows::Forms::TabControl());
            this->fcgtabPageAudioMain = (gcnew System::Windows::Forms::TabPage());
            this->fcgCXAudioDelayCut = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBAudioDelayCut = (gcnew System::Windows::Forms::Label());
            this->fcgCBAudioEncTiming = (gcnew System::Windows::Forms::Label());
            this->fcgCXAudioEncTiming = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXAudioTempDir = (gcnew System::Windows::Forms::ComboBox());
            this->fcgTXCustomAudioTempDir = (gcnew System::Windows::Forms::TextBox());
            this->fcgBTCustomAudioTempDir = (gcnew System::Windows::Forms::Button());
            this->fcgCBAudioUsePipe = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBAudioBitrate = (gcnew System::Windows::Forms::Label());
            this->fcgNUAudioBitrate = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCBAudio2pass = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCXAudioEncMode = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBAudioEncMode = (gcnew System::Windows::Forms::Label());
            this->fcgBTAudioEncoderPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXAudioEncoderPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBAudioEncoderPath = (gcnew System::Windows::Forms::Label());
            this->fcgCBAudioOnly = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCBFAWCheck = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCXAudioEncoder = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBAudioEncoder = (gcnew System::Windows::Forms::Label());
            this->fcgLBAudioTemp = (gcnew System::Windows::Forms::Label());
            this->fcgtabPageAudioOther = (gcnew System::Windows::Forms::TabPage());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->fcgLBBatAfterAudioString = (gcnew System::Windows::Forms::Label());
            this->fcgLBBatBeforeAudioString = (gcnew System::Windows::Forms::Label());
            this->fcgBTBatAfterAudioPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXBatAfterAudioPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBBatAfterAudioPath = (gcnew System::Windows::Forms::Label());
            this->fcgCBRunBatAfterAudio = (gcnew System::Windows::Forms::CheckBox());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->fcgBTBatBeforeAudioPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXBatBeforeAudioPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBBatBeforeAudioPath = (gcnew System::Windows::Forms::Label());
            this->fcgCBRunBatBeforeAudio = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCXAudioPriority = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBAudioPriority = (gcnew System::Windows::Forms::Label());
            this->fcgPNHideTabControlVideo = (gcnew System::Windows::Forms::Panel());
            this->fcgPNHideTabControlAudio = (gcnew System::Windows::Forms::Panel());
            this->fcgPNHideTabControlMux = (gcnew System::Windows::Forms::Panel());
            this->fcgPNHideToolStripBorder = (gcnew System::Windows::Forms::Panel());
            this->fcgtabControlVideo->SuspendLayout();
            this->fcgtabPageSVTAV1_1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUEnableTF))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUTFStrength))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUVarianceOctile))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNULumaQPBias))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUSharpness))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUVarianceBoostStrength))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNULookahead))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUOverShootPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUUnderShootPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMaxSectionPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMinSectionPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUFilmGrain))->BeginInit();
            this->fcggroupBoxColorMatrix->SuspendLayout();
            this->fcgGroupBoxAspectRatio->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUAspectRatioY))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUAspectRatioX))->BeginInit();
            this->fcgPNX264Mode->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUBitrate))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUQP))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMaxQP))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMinQP))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUTileColumns))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUTileRows))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUIntraRefreshType))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUKeyint))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUThreads))->BeginInit();
            this->fcgtabPageSVTAV1_2->SuspendLayout();
            this->fcgtabPageExSettings->SuspendLayout();
            this->fcggroupBoxCmdEx->SuspendLayout();
            this->fcggroupBoxExSettings->SuspendLayout();
            this->fcgCSExeFiles->SuspendLayout();
            this->fcgtoolStripSettings->SuspendLayout();
            this->fcgtabControlMux->SuspendLayout();
            this->fcgtabPageMP4->SuspendLayout();
            this->fcgtabPageMKV->SuspendLayout();
            this->fcgtabPageMux->SuspendLayout();
            this->fcgtabPageBat->SuspendLayout();
            this->fcgtabControlAudio->SuspendLayout();
            this->fcgtabPageAudioMain->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUAudioBitrate))->BeginInit();
            this->fcgtabPageAudioOther->SuspendLayout();
            this->fcgPNHideTabControlVideo->SuspendLayout();
            this->fcgPNHideTabControlAudio->SuspendLayout();
            this->fcgPNHideTabControlMux->SuspendLayout();
            this->SuspendLayout();
            // 
            // fcgtabControlVideo
            // 
            this->fcgtabControlVideo->Controls->Add(this->fcgtabPageSVTAV1_1);
            this->fcgtabControlVideo->Controls->Add(this->fcgtabPageSVTAV1_2);
            this->fcgtabControlVideo->Controls->Add(this->fcgtabPageExSettings);
            this->fcgtabControlVideo->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgtabControlVideo->Location = System::Drawing::Point(2, 2);
            this->fcgtabControlVideo->Name = L"fcgtabControlVideo";
            this->fcgtabControlVideo->SelectedIndex = 0;
            this->fcgtabControlVideo->Size = System::Drawing::Size(616, 545);
            this->fcgtabControlVideo->TabIndex = 0;
            // 
            // fcgtabPageSVTAV1_1
            // 
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUEnableTF);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUTFStrength);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBTFStrength);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUVarianceOctile);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSharpness);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNULumaQPBias);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBLumaQPBias);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUSharpness);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBVarianceOctile);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUVarianceBoostStrength);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableVarianceBoost);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBLookahead);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNULookahead);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBFastDecode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBFastDecode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBTune);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXTune);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBOverShootPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUOverShootPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBUnderShootPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUUnderShootPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMaxSectionPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUMaxSectionPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMinSectionPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUMinSectionPct);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXMaxTXSize);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMaxTXSize);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXSCM);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBScm);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBEnableCDEF);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableCDEF);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBFilmGrain);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUFilmGrain);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableTF);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBEnableOverlay);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableOverlay);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBEnableDLF);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableDLF);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBEnableRestorationFilter);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSceneChangeDetection);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBSceneChangeDetection);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcggroupBoxColorMatrix);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgGroupBoxAspectRatio);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXHierarchicalLevels);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgPNX264Mode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLB2pasAuto);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCB2PassAuto);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXProfileAV1);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBProfileAV1);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXColorFormat);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBColorFormat);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableRestortionFiltering);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMaxQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUMaxQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMinQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUMinQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableMfmv);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMfmv);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBAQ);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXAQ);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBHierarchicalLevels);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBTile2);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUTileColumns);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBTile);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUTileRows);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBIntraRefreshType);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUIntraRefreshType);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBKeyint);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUKeyint);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBThreads);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUThreads);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBUsehighbit);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgBTX264Path);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgTXX264Path);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBX264Path);
            this->fcgtabPageSVTAV1_1->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageSVTAV1_1->Name = L"fcgtabPageSVTAV1_1";
            this->fcgtabPageSVTAV1_1->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
            this->fcgtabPageSVTAV1_1->Size = System::Drawing::Size(608, 518);
            this->fcgtabPageSVTAV1_1->TabIndex = 0;
            this->fcgtabPageSVTAV1_1->Text = L"SVT-AV1 (1)";
            this->fcgtabPageSVTAV1_1->UseVisualStyleBackColor = true;
            // 
            // fcgNUEnableTF
            // 
            this->fcgNUEnableTF->Location = System::Drawing::Point(102, 338);
            this->fcgNUEnableTF->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
            this->fcgNUEnableTF->Name = L"fcgNUEnableTF";
            this->fcgNUEnableTF->Size = System::Drawing::Size(64, 21);
            this->fcgNUEnableTF->TabIndex = 288;
            this->fcgNUEnableTF->Tag = L"reCmd";
            this->fcgNUEnableTF->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgNUTFStrength
            // 
            this->fcgNUTFStrength->Location = System::Drawing::Point(286, 339);
            this->fcgNUTFStrength->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
            this->fcgNUTFStrength->Name = L"fcgNUTFStrength";
            this->fcgNUTFStrength->Size = System::Drawing::Size(64, 21);
            this->fcgNUTFStrength->TabIndex = 287;
            this->fcgNUTFStrength->Tag = L"reCmd";
            this->fcgNUTFStrength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBTFStrength
            // 
            this->fcgLBTFStrength->AutoSize = true;
            this->fcgLBTFStrength->Location = System::Drawing::Point(189, 341);
            this->fcgLBTFStrength->Name = L"fcgLBTFStrength";
            this->fcgLBTFStrength->Size = System::Drawing::Size(67, 14);
            this->fcgLBTFStrength->TabIndex = 286;
            this->fcgLBTFStrength->Text = L"TFStrength";
            // 
            // fcgNUVarianceOctile
            // 
            this->fcgNUVarianceOctile->Location = System::Drawing::Point(286, 367);
            this->fcgNUVarianceOctile->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8, 0, 0, 0 });
            this->fcgNUVarianceOctile->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->fcgNUVarianceOctile->Name = L"fcgNUVarianceOctile";
            this->fcgNUVarianceOctile->Size = System::Drawing::Size(64, 21);
            this->fcgNUVarianceOctile->TabIndex = 285;
            this->fcgNUVarianceOctile->Tag = L"reCmd";
            this->fcgNUVarianceOctile->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            this->fcgNUVarianceOctile->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            // 
            // fcgLBSharpness
            // 
            this->fcgLBSharpness->AutoSize = true;
            this->fcgLBSharpness->Location = System::Drawing::Point(189, 397);
            this->fcgLBSharpness->Name = L"fcgLBSharpness";
            this->fcgLBSharpness->Size = System::Drawing::Size(62, 14);
            this->fcgLBSharpness->TabIndex = 284;
            this->fcgLBSharpness->Text = L"Sharpness";
            // 
            // fcgNULumaQPBias
            // 
            this->fcgNULumaQPBias->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNULumaQPBias->Location = System::Drawing::Point(102, 394);
            this->fcgNULumaQPBias->Name = L"fcgNULumaQPBias";
            this->fcgNULumaQPBias->Size = System::Drawing::Size(64, 21);
            this->fcgNULumaQPBias->TabIndex = 283;
            this->fcgNULumaQPBias->Tag = L"reCmd";
            this->fcgNULumaQPBias->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBLumaQPBias
            // 
            this->fcgLBLumaQPBias->AutoSize = true;
            this->fcgLBLumaQPBias->Location = System::Drawing::Point(10, 396);
            this->fcgLBLumaQPBias->Name = L"fcgLBLumaQPBias";
            this->fcgLBLumaQPBias->Size = System::Drawing::Size(73, 14);
            this->fcgLBLumaQPBias->TabIndex = 282;
            this->fcgLBLumaQPBias->Text = L"LumaQpBias";
            // 
            // fcgNUSharpness
            // 
            this->fcgNUSharpness->Location = System::Drawing::Point(286, 394);
            this->fcgNUSharpness->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
            this->fcgNUSharpness->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, System::Int32::MinValue });
            this->fcgNUSharpness->Name = L"fcgNUSharpness";
            this->fcgNUSharpness->Size = System::Drawing::Size(64, 21);
            this->fcgNUSharpness->TabIndex = 281;
            this->fcgNUSharpness->Tag = L"reCmd";
            this->fcgNUSharpness->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBVarianceOctile
            // 
            this->fcgLBVarianceOctile->AutoSize = true;
            this->fcgLBVarianceOctile->Location = System::Drawing::Point(189, 369);
            this->fcgLBVarianceOctile->Name = L"fcgLBVarianceOctile";
            this->fcgLBVarianceOctile->Size = System::Drawing::Size(83, 14);
            this->fcgLBVarianceOctile->TabIndex = 280;
            this->fcgLBVarianceOctile->Text = L"VarianceOctile";
            // 
            // fcgNUVarianceBoostStrength
            // 
            this->fcgNUVarianceBoostStrength->Location = System::Drawing::Point(102, 367);
            this->fcgNUVarianceBoostStrength->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
            this->fcgNUVarianceBoostStrength->Name = L"fcgNUVarianceBoostStrength";
            this->fcgNUVarianceBoostStrength->Size = System::Drawing::Size(64, 21);
            this->fcgNUVarianceBoostStrength->TabIndex = 279;
            this->fcgNUVarianceBoostStrength->Tag = L"reCmd";
            this->fcgNUVarianceBoostStrength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBEnableVarianceBoost
            // 
            this->fcgLBEnableVarianceBoost->AutoSize = true;
            this->fcgLBEnableVarianceBoost->Location = System::Drawing::Point(10, 369);
            this->fcgLBEnableVarianceBoost->Name = L"fcgLBEnableVarianceBoost";
            this->fcgLBEnableVarianceBoost->Size = System::Drawing::Size(83, 14);
            this->fcgLBEnableVarianceBoost->TabIndex = 277;
            this->fcgLBEnableVarianceBoost->Text = L"VarianceBoost";
            // 
            // fcgLBLookahead
            // 
            this->fcgLBLookahead->AutoSize = true;
            this->fcgLBLookahead->Location = System::Drawing::Point(415, 179);
            this->fcgLBLookahead->Name = L"fcgLBLookahead";
            this->fcgLBLookahead->Size = System::Drawing::Size(65, 14);
            this->fcgLBLookahead->TabIndex = 276;
            this->fcgLBLookahead->Text = L"Lookahead";
            // 
            // fcgNULookahead
            // 
            this->fcgNULookahead->Location = System::Drawing::Point(526, 177);
            this->fcgNULookahead->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
            this->fcgNULookahead->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
            this->fcgNULookahead->Name = L"fcgNULookahead";
            this->fcgNULookahead->Size = System::Drawing::Size(64, 21);
            this->fcgNULookahead->TabIndex = 275;
            this->fcgNULookahead->Tag = L"reCmd";
            this->fcgNULookahead->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            this->fcgNULookahead->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
            // 
            // fcgLBFastDecode
            // 
            this->fcgLBFastDecode->AutoSize = true;
            this->fcgLBFastDecode->Location = System::Drawing::Point(416, 225);
            this->fcgLBFastDecode->Name = L"fcgLBFastDecode";
            this->fcgLBFastDecode->Size = System::Drawing::Size(72, 14);
            this->fcgLBFastDecode->TabIndex = 274;
            this->fcgLBFastDecode->Text = L"Fast Decode";
            // 
            // fcgCBFastDecode
            // 
            this->fcgCBFastDecode->AutoSize = true;
            this->fcgCBFastDecode->Location = System::Drawing::Point(526, 227);
            this->fcgCBFastDecode->Name = L"fcgCBFastDecode";
            this->fcgCBFastDecode->Size = System::Drawing::Size(15, 14);
            this->fcgCBFastDecode->TabIndex = 273;
            this->fcgCBFastDecode->Tag = L"reCmd";
            this->fcgCBFastDecode->UseVisualStyleBackColor = true;
            // 
            // fcgLBTune
            // 
            this->fcgLBTune->AutoSize = true;
            this->fcgLBTune->Location = System::Drawing::Point(10, 146);
            this->fcgLBTune->Name = L"fcgLBTune";
            this->fcgLBTune->Size = System::Drawing::Size(31, 14);
            this->fcgLBTune->TabIndex = 272;
            this->fcgLBTune->Text = L"tune";
            // 
            // fcgCXTune
            // 
            this->fcgCXTune->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXTune->FormattingEnabled = true;
            this->fcgCXTune->Location = System::Drawing::Point(130, 143);
            this->fcgCXTune->Name = L"fcgCXTune";
            this->fcgCXTune->Size = System::Drawing::Size(118, 22);
            this->fcgCXTune->TabIndex = 271;
            this->fcgCXTune->Tag = L"reCmd";
            // 
            // fcgLBOverShootPct
            // 
            this->fcgLBOverShootPct->AutoSize = true;
            this->fcgLBOverShootPct->Location = System::Drawing::Point(190, 451);
            this->fcgLBOverShootPct->Name = L"fcgLBOverShootPct";
            this->fcgLBOverShootPct->Size = System::Drawing::Size(81, 14);
            this->fcgLBOverShootPct->TabIndex = 269;
            this->fcgLBOverShootPct->Text = L"OverShootPct";
            // 
            // fcgNUOverShootPct
            // 
            this->fcgNUOverShootPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUOverShootPct->Location = System::Drawing::Point(286, 450);
            this->fcgNUOverShootPct->Name = L"fcgNUOverShootPct";
            this->fcgNUOverShootPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUOverShootPct->TabIndex = 265;
            this->fcgNUOverShootPct->Tag = L"reCmd";
            this->fcgNUOverShootPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBUnderShootPct
            // 
            this->fcgLBUnderShootPct->AutoSize = true;
            this->fcgLBUnderShootPct->Location = System::Drawing::Point(190, 424);
            this->fcgLBUnderShootPct->Name = L"fcgLBUnderShootPct";
            this->fcgLBUnderShootPct->Size = System::Drawing::Size(89, 14);
            this->fcgLBUnderShootPct->TabIndex = 268;
            this->fcgLBUnderShootPct->Text = L"UnderShootPct";
            // 
            // fcgNUUnderShootPct
            // 
            this->fcgNUUnderShootPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUUnderShootPct->Location = System::Drawing::Point(286, 422);
            this->fcgNUUnderShootPct->Name = L"fcgNUUnderShootPct";
            this->fcgNUUnderShootPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUUnderShootPct->TabIndex = 264;
            this->fcgNUUnderShootPct->Tag = L"reCmd";
            this->fcgNUUnderShootPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBMaxSectionPct
            // 
            this->fcgLBMaxSectionPct->AutoSize = true;
            this->fcgLBMaxSectionPct->Location = System::Drawing::Point(10, 451);
            this->fcgLBMaxSectionPct->Name = L"fcgLBMaxSectionPct";
            this->fcgLBMaxSectionPct->Size = System::Drawing::Size(85, 14);
            this->fcgLBMaxSectionPct->TabIndex = 267;
            this->fcgLBMaxSectionPct->Text = L"MaxSectionPct";
            // 
            // fcgNUMaxSectionPct
            // 
            this->fcgNUMaxSectionPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUMaxSectionPct->Location = System::Drawing::Point(102, 450);
            this->fcgNUMaxSectionPct->Name = L"fcgNUMaxSectionPct";
            this->fcgNUMaxSectionPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUMaxSectionPct->TabIndex = 263;
            this->fcgNUMaxSectionPct->Tag = L"reCmd";
            this->fcgNUMaxSectionPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBMinSectionPct
            // 
            this->fcgLBMinSectionPct->AutoSize = true;
            this->fcgLBMinSectionPct->Location = System::Drawing::Point(10, 424);
            this->fcgLBMinSectionPct->Name = L"fcgLBMinSectionPct";
            this->fcgLBMinSectionPct->Size = System::Drawing::Size(83, 14);
            this->fcgLBMinSectionPct->TabIndex = 266;
            this->fcgLBMinSectionPct->Text = L"MinSectionPct";
            // 
            // fcgNUMinSectionPct
            // 
            this->fcgNUMinSectionPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUMinSectionPct->Location = System::Drawing::Point(102, 422);
            this->fcgNUMinSectionPct->Name = L"fcgNUMinSectionPct";
            this->fcgNUMinSectionPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUMinSectionPct->TabIndex = 262;
            this->fcgNUMinSectionPct->Tag = L"reCmd";
            this->fcgNUMinSectionPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCXMaxTXSize
            // 
            this->fcgCXMaxTXSize->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMaxTXSize->FormattingEnabled = true;
            this->fcgCXMaxTXSize->Location = System::Drawing::Point(286, 475);
            this->fcgCXMaxTXSize->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
            this->fcgCXMaxTXSize->Name = L"fcgCXMaxTXSize";
            this->fcgCXMaxTXSize->Size = System::Drawing::Size(64, 22);
            this->fcgCXMaxTXSize->TabIndex = 291;
            this->fcgCXMaxTXSize->Tag = L"reCmd";
            // 
            // fcgLBMaxTXSize
            // 
            this->fcgLBMaxTXSize->AutoSize = true;
            this->fcgLBMaxTXSize->Location = System::Drawing::Point(190, 478);
            this->fcgLBMaxTXSize->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->fcgLBMaxTXSize->Name = L"fcgLBMaxTXSize";
            this->fcgLBMaxTXSize->Size = System::Drawing::Size(64, 14);
            this->fcgLBMaxTXSize->TabIndex = 290;
            this->fcgLBMaxTXSize->Text = L"MaxTXSize";
            // 
            // fcgCXSCM
            // 
            this->fcgCXSCM->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXSCM->FormattingEnabled = true;
            this->fcgCXSCM->Location = System::Drawing::Point(131, 251);
            this->fcgCXSCM->Name = L"fcgCXSCM";
            this->fcgCXSCM->Size = System::Drawing::Size(118, 22);
            this->fcgCXSCM->TabIndex = 259;
            this->fcgCXSCM->Tag = L"reCmd";
            // 
            // fcgLBScm
            // 
            this->fcgLBScm->AutoSize = true;
            this->fcgLBScm->Location = System::Drawing::Point(10, 254);
            this->fcgLBScm->Name = L"fcgLBScm";
            this->fcgLBScm->Size = System::Drawing::Size(115, 14);
            this->fcgLBScm->TabIndex = 260;
            this->fcgLBScm->Text = L"ScreenContentMode";
            // 
            // fcgCBEnableCDEF
            // 
            this->fcgCBEnableCDEF->AutoSize = true;
            this->fcgCBEnableCDEF->Location = System::Drawing::Point(298, 286);
            this->fcgCBEnableCDEF->Name = L"fcgCBEnableCDEF";
            this->fcgCBEnableCDEF->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableCDEF->TabIndex = 258;
            this->fcgCBEnableCDEF->Tag = L"reCmd";
            this->fcgCBEnableCDEF->UseVisualStyleBackColor = true;
            // 
            // fcgLBEnableCDEF
            // 
            this->fcgLBEnableCDEF->AutoSize = true;
            this->fcgLBEnableCDEF->Location = System::Drawing::Point(190, 285);
            this->fcgLBEnableCDEF->Name = L"fcgLBEnableCDEF";
            this->fcgLBEnableCDEF->Size = System::Drawing::Size(71, 14);
            this->fcgLBEnableCDEF->TabIndex = 257;
            this->fcgLBEnableCDEF->Text = L"EnableCDEF";
            // 
            // fcgLBFilmGrain
            // 
            this->fcgLBFilmGrain->AutoSize = true;
            this->fcgLBFilmGrain->Location = System::Drawing::Point(10, 478);
            this->fcgLBFilmGrain->Name = L"fcgLBFilmGrain";
            this->fcgLBFilmGrain->Size = System::Drawing::Size(59, 14);
            this->fcgLBFilmGrain->TabIndex = 256;
            this->fcgLBFilmGrain->Text = L"FilmGrain";
            // 
            // fcgNUFilmGrain
            // 
            this->fcgNUFilmGrain->Location = System::Drawing::Point(102, 476);
            this->fcgNUFilmGrain->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->fcgNUFilmGrain->Name = L"fcgNUFilmGrain";
            this->fcgNUFilmGrain->Size = System::Drawing::Size(64, 21);
            this->fcgNUFilmGrain->TabIndex = 255;
            this->fcgNUFilmGrain->Tag = L"reCmd";
            this->fcgNUFilmGrain->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBEnableTF
            // 
            this->fcgLBEnableTF->AutoSize = true;
            this->fcgLBEnableTF->Location = System::Drawing::Point(10, 339);
            this->fcgLBEnableTF->Name = L"fcgLBEnableTF";
            this->fcgLBEnableTF->Size = System::Drawing::Size(55, 14);
            this->fcgLBEnableTF->TabIndex = 235;
            this->fcgLBEnableTF->Text = L"EnableTF";
            // 
            // fcgCBEnableOverlay
            // 
            this->fcgCBEnableOverlay->AutoSize = true;
            this->fcgCBEnableOverlay->Location = System::Drawing::Point(110, 314);
            this->fcgCBEnableOverlay->Name = L"fcgCBEnableOverlay";
            this->fcgCBEnableOverlay->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableOverlay->TabIndex = 234;
            this->fcgCBEnableOverlay->Tag = L"reCmd";
            this->fcgCBEnableOverlay->UseVisualStyleBackColor = true;
            // 
            // fcgLBEnableOverlay
            // 
            this->fcgLBEnableOverlay->AutoSize = true;
            this->fcgLBEnableOverlay->Location = System::Drawing::Point(10, 312);
            this->fcgLBEnableOverlay->Name = L"fcgLBEnableOverlay";
            this->fcgLBEnableOverlay->Size = System::Drawing::Size(83, 14);
            this->fcgLBEnableOverlay->TabIndex = 233;
            this->fcgLBEnableOverlay->Text = L"EnableOverlay";
            // 
            // fcgCBEnableDLF
            // 
            this->fcgCBEnableDLF->AutoSize = true;
            this->fcgCBEnableDLF->Location = System::Drawing::Point(110, 286);
            this->fcgCBEnableDLF->Name = L"fcgCBEnableDLF";
            this->fcgCBEnableDLF->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableDLF->TabIndex = 232;
            this->fcgCBEnableDLF->Tag = L"reCmd";
            this->fcgCBEnableDLF->UseVisualStyleBackColor = true;
            // 
            // fcgLBEnableDLF
            // 
            this->fcgLBEnableDLF->AutoSize = true;
            this->fcgLBEnableDLF->Location = System::Drawing::Point(10, 285);
            this->fcgLBEnableDLF->Name = L"fcgLBEnableDLF";
            this->fcgLBEnableDLF->Size = System::Drawing::Size(63, 14);
            this->fcgLBEnableDLF->TabIndex = 231;
            this->fcgLBEnableDLF->Text = L"EnableDLF";
            // 
            // fcgCBEnableRestorationFilter
            // 
            this->fcgCBEnableRestorationFilter->AutoSize = true;
            this->fcgCBEnableRestorationFilter->Location = System::Drawing::Point(298, 314);
            this->fcgCBEnableRestorationFilter->Name = L"fcgCBEnableRestorationFilter";
            this->fcgCBEnableRestorationFilter->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableRestorationFilter->TabIndex = 230;
            this->fcgCBEnableRestorationFilter->Tag = L"reCmd";
            this->fcgCBEnableRestorationFilter->UseVisualStyleBackColor = true;
            // 
            // fcgLBSceneChangeDetection
            // 
            this->fcgLBSceneChangeDetection->AutoSize = true;
            this->fcgLBSceneChangeDetection->Location = System::Drawing::Point(416, 204);
            this->fcgLBSceneChangeDetection->Name = L"fcgLBSceneChangeDetection";
            this->fcgLBSceneChangeDetection->Size = System::Drawing::Size(83, 14);
            this->fcgLBSceneChangeDetection->TabIndex = 228;
            this->fcgLBSceneChangeDetection->Text = L"Scene Change";
            // 
            // fcgCBSceneChangeDetection
            // 
            this->fcgCBSceneChangeDetection->AutoSize = true;
            this->fcgCBSceneChangeDetection->Location = System::Drawing::Point(526, 206);
            this->fcgCBSceneChangeDetection->Name = L"fcgCBSceneChangeDetection";
            this->fcgCBSceneChangeDetection->Size = System::Drawing::Size(15, 14);
            this->fcgCBSceneChangeDetection->TabIndex = 227;
            this->fcgCBSceneChangeDetection->Tag = L"reCmd";
            this->fcgCBSceneChangeDetection->UseVisualStyleBackColor = true;
            // 
            // fcggroupBoxColorMatrix
            // 
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXColorRange);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBInputRange);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXTransfer);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXColorPrim);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXColorMatrix);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBTransfer);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBColorPrim);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBColorMatrix);
            this->fcggroupBoxColorMatrix->Location = System::Drawing::Point(377, 364);
            this->fcggroupBoxColorMatrix->Name = L"fcggroupBoxColorMatrix";
            this->fcggroupBoxColorMatrix->Size = System::Drawing::Size(222, 145);
            this->fcggroupBoxColorMatrix->TabIndex = 90;
            this->fcggroupBoxColorMatrix->TabStop = false;
            this->fcggroupBoxColorMatrix->Text = L"色空間";
            // 
            // fcgCXColorRange
            // 
            this->fcgCXColorRange->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXColorRange->FormattingEnabled = true;
            this->fcgCXColorRange->Location = System::Drawing::Point(92, 114);
            this->fcgCXColorRange->Name = L"fcgCXColorRange";
            this->fcgCXColorRange->Size = System::Drawing::Size(120, 22);
            this->fcgCXColorRange->TabIndex = 4;
            this->fcgCXColorRange->Tag = L"reCmd";
            // 
            // fcgLBInputRange
            // 
            this->fcgLBInputRange->AutoSize = true;
            this->fcgLBInputRange->Location = System::Drawing::Point(8, 117);
            this->fcgLBInputRange->Name = L"fcgLBInputRange";
            this->fcgLBInputRange->Size = System::Drawing::Size(70, 14);
            this->fcgLBInputRange->TabIndex = 3;
            this->fcgLBInputRange->Text = L"color range";
            // 
            // fcgCXTransfer
            // 
            this->fcgCXTransfer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXTransfer->FormattingEnabled = true;
            this->fcgCXTransfer->Location = System::Drawing::Point(92, 83);
            this->fcgCXTransfer->Name = L"fcgCXTransfer";
            this->fcgCXTransfer->Size = System::Drawing::Size(120, 22);
            this->fcgCXTransfer->TabIndex = 2;
            this->fcgCXTransfer->Tag = L"reCmd";
            // 
            // fcgCXColorPrim
            // 
            this->fcgCXColorPrim->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXColorPrim->FormattingEnabled = true;
            this->fcgCXColorPrim->Location = System::Drawing::Point(92, 51);
            this->fcgCXColorPrim->Name = L"fcgCXColorPrim";
            this->fcgCXColorPrim->Size = System::Drawing::Size(120, 22);
            this->fcgCXColorPrim->TabIndex = 1;
            this->fcgCXColorPrim->Tag = L"reCmd";
            // 
            // fcgCXColorMatrix
            // 
            this->fcgCXColorMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXColorMatrix->FormattingEnabled = true;
            this->fcgCXColorMatrix->Location = System::Drawing::Point(92, 20);
            this->fcgCXColorMatrix->Name = L"fcgCXColorMatrix";
            this->fcgCXColorMatrix->Size = System::Drawing::Size(120, 22);
            this->fcgCXColorMatrix->TabIndex = 0;
            this->fcgCXColorMatrix->Tag = L"reCmd";
            // 
            // fcgLBTransfer
            // 
            this->fcgLBTransfer->AutoSize = true;
            this->fcgLBTransfer->Location = System::Drawing::Point(8, 86);
            this->fcgLBTransfer->Name = L"fcgLBTransfer";
            this->fcgLBTransfer->Size = System::Drawing::Size(49, 14);
            this->fcgLBTransfer->TabIndex = 2;
            this->fcgLBTransfer->Text = L"transfer";
            // 
            // fcgLBColorPrim
            // 
            this->fcgLBColorPrim->AutoSize = true;
            this->fcgLBColorPrim->Location = System::Drawing::Point(8, 54);
            this->fcgLBColorPrim->Name = L"fcgLBColorPrim";
            this->fcgLBColorPrim->Size = System::Drawing::Size(61, 14);
            this->fcgLBColorPrim->TabIndex = 1;
            this->fcgLBColorPrim->Text = L"colorprim";
            // 
            // fcgLBColorMatrix
            // 
            this->fcgLBColorMatrix->AutoSize = true;
            this->fcgLBColorMatrix->Location = System::Drawing::Point(8, 23);
            this->fcgLBColorMatrix->Name = L"fcgLBColorMatrix";
            this->fcgLBColorMatrix->Size = System::Drawing::Size(70, 14);
            this->fcgLBColorMatrix->TabIndex = 0;
            this->fcgLBColorMatrix->Text = L"colormatrix";
            // 
            // fcgGroupBoxAspectRatio
            // 
            this->fcgGroupBoxAspectRatio->Controls->Add(this->fcgNUAspectRatioY);
            this->fcgGroupBoxAspectRatio->Controls->Add(this->fcgLBAspectRatio);
            this->fcgGroupBoxAspectRatio->Controls->Add(this->fcgNUAspectRatioX);
            this->fcgGroupBoxAspectRatio->Controls->Add(this->fcgCXAspectRatio);
            this->fcgGroupBoxAspectRatio->Location = System::Drawing::Point(393, 3);
            this->fcgGroupBoxAspectRatio->Name = L"fcgGroupBoxAspectRatio";
            this->fcgGroupBoxAspectRatio->Size = System::Drawing::Size(205, 75);
            this->fcgGroupBoxAspectRatio->TabIndex = 40;
            this->fcgGroupBoxAspectRatio->TabStop = false;
            this->fcgGroupBoxAspectRatio->Text = L"アスペクト比";
            // 
            // fcgNUAspectRatioY
            // 
            this->fcgNUAspectRatioY->Location = System::Drawing::Point(126, 47);
            this->fcgNUAspectRatioY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
            this->fcgNUAspectRatioY->Name = L"fcgNUAspectRatioY";
            this->fcgNUAspectRatioY->Size = System::Drawing::Size(60, 21);
            this->fcgNUAspectRatioY->TabIndex = 2;
            this->fcgNUAspectRatioY->Tag = L"reCmd";
            this->fcgNUAspectRatioY->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBAspectRatio
            // 
            this->fcgLBAspectRatio->AutoSize = true;
            this->fcgLBAspectRatio->Location = System::Drawing::Point(108, 49);
            this->fcgLBAspectRatio->Name = L"fcgLBAspectRatio";
            this->fcgLBAspectRatio->Size = System::Drawing::Size(12, 14);
            this->fcgLBAspectRatio->TabIndex = 2;
            this->fcgLBAspectRatio->Text = L":";
            // 
            // fcgNUAspectRatioX
            // 
            this->fcgNUAspectRatioX->Location = System::Drawing::Point(42, 47);
            this->fcgNUAspectRatioX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
            this->fcgNUAspectRatioX->Name = L"fcgNUAspectRatioX";
            this->fcgNUAspectRatioX->Size = System::Drawing::Size(60, 21);
            this->fcgNUAspectRatioX->TabIndex = 1;
            this->fcgNUAspectRatioX->Tag = L"reCmd";
            this->fcgNUAspectRatioX->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCXAspectRatio
            // 
            this->fcgCXAspectRatio->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAspectRatio->FormattingEnabled = true;
            this->fcgCXAspectRatio->Location = System::Drawing::Point(15, 19);
            this->fcgCXAspectRatio->Name = L"fcgCXAspectRatio";
            this->fcgCXAspectRatio->Size = System::Drawing::Size(171, 22);
            this->fcgCXAspectRatio->TabIndex = 0;
            this->fcgCXAspectRatio->Tag = L"reCmd";
            // 
            // fcgCXHierarchicalLevels
            // 
            this->fcgCXHierarchicalLevels->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXHierarchicalLevels->FormattingEnabled = true;
            this->fcgCXHierarchicalLevels->Location = System::Drawing::Point(130, 195);
            this->fcgCXHierarchicalLevels->Name = L"fcgCXHierarchicalLevels";
            this->fcgCXHierarchicalLevels->Size = System::Drawing::Size(118, 22);
            this->fcgCXHierarchicalLevels->TabIndex = 21;
            this->fcgCXHierarchicalLevels->Tag = L"reCmd";
            // 
            // fcgPNX264Mode
            // 
            this->fcgPNX264Mode->Controls->Add(this->fcgLBKbps);
            this->fcgPNX264Mode->Controls->Add(this->fcgLBRC);
            this->fcgPNX264Mode->Controls->Add(this->fcgLBEncMode);
            this->fcgPNX264Mode->Controls->Add(this->fcgNUBitrate);
            this->fcgPNX264Mode->Controls->Add(this->fcgCXEncMode);
            this->fcgPNX264Mode->Controls->Add(this->fcgNUQP);
            this->fcgPNX264Mode->Controls->Add(this->fcgCXRC);
            this->fcgPNX264Mode->Location = System::Drawing::Point(5, 67);
            this->fcgPNX264Mode->Name = L"fcgPNX264Mode";
            this->fcgPNX264Mode->Size = System::Drawing::Size(376, 71);
            this->fcgPNX264Mode->TabIndex = 4;
            // 
            // fcgLBKbps
            // 
            this->fcgLBKbps->AutoSize = true;
            this->fcgLBKbps->Location = System::Drawing::Point(334, 10);
            this->fcgLBKbps->Name = L"fcgLBKbps";
            this->fcgLBKbps->Size = System::Drawing::Size(32, 14);
            this->fcgLBKbps->TabIndex = 76;
            this->fcgLBKbps->Text = L"kbps";
            // 
            // fcgLBRC
            // 
            this->fcgLBRC->AutoSize = true;
            this->fcgLBRC->Location = System::Drawing::Point(4, 10);
            this->fcgLBRC->Name = L"fcgLBRC";
            this->fcgLBRC->Size = System::Drawing::Size(54, 14);
            this->fcgLBRC->TabIndex = 75;
            this->fcgLBRC->Text = L"レート制御";
            // 
            // fcgLBEncMode
            // 
            this->fcgLBEncMode->AutoSize = true;
            this->fcgLBEncMode->Location = System::Drawing::Point(4, 44);
            this->fcgLBEncMode->Name = L"fcgLBEncMode";
            this->fcgLBEncMode->Size = System::Drawing::Size(51, 14);
            this->fcgLBEncMode->TabIndex = 74;
            this->fcgLBEncMode->Text = L"速度設定";
            // 
            // fcgNUBitrate
            // 
            this->fcgNUBitrate->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
            this->fcgNUBitrate->Location = System::Drawing::Point(249, 8);
            this->fcgNUBitrate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4294967, 0, 0, 0 });
            this->fcgNUBitrate->Name = L"fcgNUBitrate";
            this->fcgNUBitrate->Size = System::Drawing::Size(79, 21);
            this->fcgNUBitrate->TabIndex = 6;
            this->fcgNUBitrate->Tag = L"reCmd";
            this->fcgNUBitrate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            this->fcgNUBitrate->Visible = false;
            // 
            // fcgCXEncMode
            // 
            this->fcgCXEncMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEncMode->FormattingEnabled = true;
            this->fcgCXEncMode->Location = System::Drawing::Point(79, 41);
            this->fcgCXEncMode->Name = L"fcgCXEncMode";
            this->fcgCXEncMode->Size = System::Drawing::Size(164, 22);
            this->fcgCXEncMode->TabIndex = 7;
            this->fcgCXEncMode->Tag = L"reCmd";
            // 
            // fcgNUQP
            // 
            this->fcgNUQP->Location = System::Drawing::Point(257, 8);
            this->fcgNUQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 63, 0, 0, 0 });
            this->fcgNUQP->Name = L"fcgNUQP";
            this->fcgNUQP->Size = System::Drawing::Size(64, 21);
            this->fcgNUQP->TabIndex = 65;
            this->fcgNUQP->Tag = L"reCmd";
            this->fcgNUQP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            this->fcgNUQP->ValueChanged += gcnew System::EventHandler(this, &frmConfig::fcgNUQP_ValueChanged);
            // 
            // fcgCXRC
            // 
            this->fcgCXRC->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXRC->FormattingEnabled = true;
            this->fcgCXRC->Location = System::Drawing::Point(79, 7);
            this->fcgCXRC->Name = L"fcgCXRC";
            this->fcgCXRC->Size = System::Drawing::Size(164, 22);
            this->fcgCXRC->TabIndex = 5;
            this->fcgCXRC->Tag = L"reCmd";
            this->fcgCXRC->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfig::fcgCXRC_SelectedIndexChanged);
            // 
            // fcgLB2pasAuto
            // 
            this->fcgLB2pasAuto->AutoSize = true;
            this->fcgLB2pasAuto->Location = System::Drawing::Point(416, 82);
            this->fcgLB2pasAuto->Name = L"fcgLB2pasAuto";
            this->fcgLB2pasAuto->Size = System::Drawing::Size(70, 14);
            this->fcgLB2pasAuto->TabIndex = 226;
            this->fcgLB2pasAuto->Text = L"2pass Mode";
            // 
            // fcgCB2PassAuto
            // 
            this->fcgCB2PassAuto->AutoSize = true;
            this->fcgCB2PassAuto->Location = System::Drawing::Point(526, 83);
            this->fcgCB2PassAuto->Name = L"fcgCB2PassAuto";
            this->fcgCB2PassAuto->Size = System::Drawing::Size(15, 14);
            this->fcgCB2PassAuto->TabIndex = 50;
            this->fcgCB2PassAuto->Tag = L"reCmd";
            this->fcgCB2PassAuto->UseVisualStyleBackColor = true;
            // 
            // fcgCXProfileAV1
            // 
            this->fcgCXProfileAV1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXProfileAV1->FormattingEnabled = true;
            this->fcgCXProfileAV1->Location = System::Drawing::Point(481, 251);
            this->fcgCXProfileAV1->Name = L"fcgCXProfileAV1";
            this->fcgCXProfileAV1->Size = System::Drawing::Size(118, 22);
            this->fcgCXProfileAV1->TabIndex = 60;
            this->fcgCXProfileAV1->Tag = L"reCmd";
            // 
            // fcgLBProfileAV1
            // 
            this->fcgLBProfileAV1->AutoSize = true;
            this->fcgLBProfileAV1->Location = System::Drawing::Point(374, 254);
            this->fcgLBProfileAV1->Name = L"fcgLBProfileAV1";
            this->fcgLBProfileAV1->Size = System::Drawing::Size(42, 14);
            this->fcgLBProfileAV1->TabIndex = 222;
            this->fcgLBProfileAV1->Text = L"Profile";
            // 
            // fcgCXColorFormat
            // 
            this->fcgCXColorFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXColorFormat->Enabled = false;
            this->fcgCXColorFormat->FormattingEnabled = true;
            this->fcgCXColorFormat->Location = System::Drawing::Point(481, 278);
            this->fcgCXColorFormat->Name = L"fcgCXColorFormat";
            this->fcgCXColorFormat->Size = System::Drawing::Size(118, 22);
            this->fcgCXColorFormat->TabIndex = 61;
            this->fcgCXColorFormat->Tag = L"reCmd";
            // 
            // fcgLBColorFormat
            // 
            this->fcgLBColorFormat->AutoSize = true;
            this->fcgLBColorFormat->Location = System::Drawing::Point(373, 281);
            this->fcgLBColorFormat->Name = L"fcgLBColorFormat";
            this->fcgLBColorFormat->Size = System::Drawing::Size(79, 14);
            this->fcgLBColorFormat->TabIndex = 220;
            this->fcgLBColorFormat->Text = L"Color Format";
            // 
            // fcgLBEnableRestortionFiltering
            // 
            this->fcgLBEnableRestortionFiltering->AutoSize = true;
            this->fcgLBEnableRestortionFiltering->Location = System::Drawing::Point(190, 312);
            this->fcgLBEnableRestortionFiltering->Name = L"fcgLBEnableRestortionFiltering";
            this->fcgLBEnableRestortionFiltering->Size = System::Drawing::Size(99, 14);
            this->fcgLBEnableRestortionFiltering->TabIndex = 189;
            this->fcgLBEnableRestortionFiltering->Text = L"EnableRestortion";
            // 
            // fcgLBMaxQP
            // 
            this->fcgLBMaxQP->AutoSize = true;
            this->fcgLBMaxQP->Location = System::Drawing::Point(519, 340);
            this->fcgLBMaxQP->Name = L"fcgLBMaxQP";
            this->fcgLBMaxQP->Size = System::Drawing::Size(12, 14);
            this->fcgLBMaxQP->TabIndex = 172;
            this->fcgLBMaxQP->Text = L"-";
            // 
            // fcgNUMaxQP
            // 
            this->fcgNUMaxQP->Location = System::Drawing::Point(534, 338);
            this->fcgNUMaxQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 63, 0, 0, 0 });
            this->fcgNUMaxQP->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
            this->fcgNUMaxQP->Name = L"fcgNUMaxQP";
            this->fcgNUMaxQP->Size = System::Drawing::Size(64, 21);
            this->fcgNUMaxQP->TabIndex = 85;
            this->fcgNUMaxQP->Tag = L"reCmd";
            this->fcgNUMaxQP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBMinQP
            // 
            this->fcgLBMinQP->AutoSize = true;
            this->fcgLBMinQP->Location = System::Drawing::Point(373, 340);
            this->fcgLBMinQP->Name = L"fcgLBMinQP";
            this->fcgLBMinQP->Size = System::Drawing::Size(71, 14);
            this->fcgLBMinQP->TabIndex = 170;
            this->fcgLBMinQP->Text = L"QP Min-Max";
            // 
            // fcgNUMinQP
            // 
            this->fcgNUMinQP->Location = System::Drawing::Point(451, 338);
            this->fcgNUMinQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 62, 0, 0, 0 });
            this->fcgNUMinQP->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
            this->fcgNUMinQP->Name = L"fcgNUMinQP";
            this->fcgNUMinQP->Size = System::Drawing::Size(64, 21);
            this->fcgNUMinQP->TabIndex = 84;
            this->fcgNUMinQP->Tag = L"reCmd";
            this->fcgNUMinQP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCXEnableMfmv
            // 
            this->fcgCXEnableMfmv->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableMfmv->FormattingEnabled = true;
            this->fcgCXEnableMfmv->Location = System::Drawing::Point(130, 223);
            this->fcgCXEnableMfmv->Name = L"fcgCXEnableMfmv";
            this->fcgCXEnableMfmv->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableMfmv->TabIndex = 25;
            this->fcgCXEnableMfmv->Tag = L"reCmd";
            // 
            // fcgLBMfmv
            // 
            this->fcgLBMfmv->AutoSize = true;
            this->fcgLBMfmv->Location = System::Drawing::Point(10, 226);
            this->fcgLBMfmv->Name = L"fcgLBMfmv";
            this->fcgLBMfmv->Size = System::Drawing::Size(86, 14);
            this->fcgLBMfmv->TabIndex = 104;
            this->fcgLBMfmv->Text = L"MotionFieldMV";
            // 
            // fcgLBAQ
            // 
            this->fcgLBAQ->AutoSize = true;
            this->fcgLBAQ->Location = System::Drawing::Point(10, 172);
            this->fcgLBAQ->Name = L"fcgLBAQ";
            this->fcgLBAQ->Size = System::Drawing::Size(22, 14);
            this->fcgLBAQ->TabIndex = 88;
            this->fcgLBAQ->Text = L"AQ";
            // 
            // fcgCXAQ
            // 
            this->fcgCXAQ->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAQ->FormattingEnabled = true;
            this->fcgCXAQ->Location = System::Drawing::Point(130, 169);
            this->fcgCXAQ->Name = L"fcgCXAQ";
            this->fcgCXAQ->Size = System::Drawing::Size(118, 22);
            this->fcgCXAQ->TabIndex = 20;
            this->fcgCXAQ->Tag = L"reCmd";
            // 
            // fcgLBHierarchicalLevels
            // 
            this->fcgLBHierarchicalLevels->AutoSize = true;
            this->fcgLBHierarchicalLevels->Location = System::Drawing::Point(10, 198);
            this->fcgLBHierarchicalLevels->Name = L"fcgLBHierarchicalLevels";
            this->fcgLBHierarchicalLevels->Size = System::Drawing::Size(103, 14);
            this->fcgLBHierarchicalLevels->TabIndex = 85;
            this->fcgLBHierarchicalLevels->Text = L"hierarchical levels";
            // 
            // fcgLBTile2
            // 
            this->fcgLBTile2->AutoSize = true;
            this->fcgLBTile2->Location = System::Drawing::Point(518, 313);
            this->fcgLBTile2->Name = L"fcgLBTile2";
            this->fcgLBTile2->Size = System::Drawing::Size(13, 14);
            this->fcgLBTile2->TabIndex = 82;
            this->fcgLBTile2->Text = L"x";
            // 
            // fcgNUTileColumns
            // 
            this->fcgNUTileColumns->Location = System::Drawing::Point(534, 310);
            this->fcgNUTileColumns->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->fcgNUTileColumns->Name = L"fcgNUTileColumns";
            this->fcgNUTileColumns->Size = System::Drawing::Size(64, 21);
            this->fcgNUTileColumns->TabIndex = 81;
            this->fcgNUTileColumns->Tag = L"reCmd";
            this->fcgNUTileColumns->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBTile
            // 
            this->fcgLBTile->AutoSize = true;
            this->fcgLBTile->Location = System::Drawing::Point(374, 314);
            this->fcgLBTile->Name = L"fcgLBTile";
            this->fcgLBTile->Size = System::Drawing::Size(23, 14);
            this->fcgLBTile->TabIndex = 77;
            this->fcgLBTile->Text = L"tile";
            // 
            // fcgNUTileRows
            // 
            this->fcgNUTileRows->Location = System::Drawing::Point(451, 310);
            this->fcgNUTileRows->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->fcgNUTileRows->Name = L"fcgNUTileRows";
            this->fcgNUTileRows->Size = System::Drawing::Size(64, 21);
            this->fcgNUTileRows->TabIndex = 80;
            this->fcgNUTileRows->Tag = L"reCmd";
            this->fcgNUTileRows->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBIntraRefreshType
            // 
            this->fcgLBIntraRefreshType->AutoSize = true;
            this->fcgLBIntraRefreshType->Location = System::Drawing::Point(415, 154);
            this->fcgLBIntraRefreshType->Name = L"fcgLBIntraRefreshType";
            this->fcgLBIntraRefreshType->Size = System::Drawing::Size(101, 14);
            this->fcgLBIntraRefreshType->TabIndex = 71;
            this->fcgLBIntraRefreshType->Text = L"intra refresh type";
            // 
            // fcgNUIntraRefreshType
            // 
            this->fcgNUIntraRefreshType->Location = System::Drawing::Point(526, 152);
            this->fcgNUIntraRefreshType->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
            this->fcgNUIntraRefreshType->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            this->fcgNUIntraRefreshType->Name = L"fcgNUIntraRefreshType";
            this->fcgNUIntraRefreshType->Size = System::Drawing::Size(64, 21);
            this->fcgNUIntraRefreshType->TabIndex = 53;
            this->fcgNUIntraRefreshType->Tag = L"reCmd";
            this->fcgNUIntraRefreshType->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            this->fcgNUIntraRefreshType->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
            // 
            // fcgLBKeyint
            // 
            this->fcgLBKeyint->AutoSize = true;
            this->fcgLBKeyint->Location = System::Drawing::Point(415, 129);
            this->fcgLBKeyint->Name = L"fcgLBKeyint";
            this->fcgLBKeyint->Size = System::Drawing::Size(39, 14);
            this->fcgLBKeyint->TabIndex = 69;
            this->fcgLBKeyint->Text = L"keyint";
            // 
            // fcgNUKeyint
            // 
            this->fcgNUKeyint->Location = System::Drawing::Point(526, 127);
            this->fcgNUKeyint->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
            this->fcgNUKeyint->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, System::Int32::MinValue });
            this->fcgNUKeyint->Name = L"fcgNUKeyint";
            this->fcgNUKeyint->Size = System::Drawing::Size(64, 21);
            this->fcgNUKeyint->TabIndex = 52;
            this->fcgNUKeyint->Tag = L"reCmd";
            this->fcgNUKeyint->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBThreads
            // 
            this->fcgLBThreads->AutoSize = true;
            this->fcgLBThreads->Location = System::Drawing::Point(416, 104);
            this->fcgLBThreads->Name = L"fcgLBThreads";
            this->fcgLBThreads->Size = System::Drawing::Size(47, 14);
            this->fcgLBThreads->TabIndex = 51;
            this->fcgLBThreads->Text = L"threads";
            // 
            // fcgNUThreads
            // 
            this->fcgNUThreads->Location = System::Drawing::Point(526, 102);
            this->fcgNUThreads->Name = L"fcgNUThreads";
            this->fcgNUThreads->Size = System::Drawing::Size(64, 21);
            this->fcgNUThreads->TabIndex = 51;
            this->fcgNUThreads->Tag = L"reCmd";
            this->fcgNUThreads->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCBUsehighbit
            // 
            this->fcgCBUsehighbit->AutoSize = true;
            this->fcgCBUsehighbit->Location = System::Drawing::Point(277, 10);
            this->fcgCBUsehighbit->Name = L"fcgCBUsehighbit";
            this->fcgCBUsehighbit->Size = System::Drawing::Size(99, 18);
            this->fcgCBUsehighbit->TabIndex = 1;
            this->fcgCBUsehighbit->Tag = L"reCmd";
            this->fcgCBUsehighbit->Text = L"highbit depth";
            this->fcgCBUsehighbit->UseVisualStyleBackColor = true;
            // 
            // fcgBTX264Path
            // 
            this->fcgBTX264Path->Location = System::Drawing::Point(354, 34);
            this->fcgBTX264Path->Name = L"fcgBTX264Path";
            this->fcgBTX264Path->Size = System::Drawing::Size(27, 22);
            this->fcgBTX264Path->TabIndex = 3;
            this->fcgBTX264Path->Text = L"...";
            this->fcgBTX264Path->UseVisualStyleBackColor = true;
            this->fcgBTX264Path->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTX264Path_Click);
            // 
            // fcgTXX264Path
            // 
            this->fcgTXX264Path->AllowDrop = true;
            this->fcgTXX264Path->Location = System::Drawing::Point(30, 35);
            this->fcgTXX264Path->Name = L"fcgTXX264Path";
            this->fcgTXX264Path->Size = System::Drawing::Size(324, 21);
            this->fcgTXX264Path->TabIndex = 2;
            this->fcgTXX264Path->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXX264Path_TextChanged);
            this->fcgTXX264Path->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXX264Path->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            this->fcgTXX264Path->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXX264Path_Enter);
            this->fcgTXX264Path->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXX264Path_Leave);
            // 
            // fcgLBX264Path
            // 
            this->fcgLBX264Path->AutoSize = true;
            this->fcgLBX264Path->Location = System::Drawing::Point(27, 11);
            this->fcgLBX264Path->Name = L"fcgLBX264Path";
            this->fcgLBX264Path->Size = System::Drawing::Size(49, 14);
            this->fcgLBX264Path->TabIndex = 2;
            this->fcgLBX264Path->Text = L"～の指定";
            // 
            // fcgtabPageSVTAV1_2
            // 
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableStatReport);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCBEnableStatReport);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBSTATUS);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgTXStatusFile);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgBTStatusFile);
            this->fcgtabPageSVTAV1_2->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageSVTAV1_2->Name = L"fcgtabPageSVTAV1_2";
            this->fcgtabPageSVTAV1_2->Size = System::Drawing::Size(608, 518);
            this->fcgtabPageSVTAV1_2->TabIndex = 4;
            this->fcgtabPageSVTAV1_2->Text = L"SVT-AV1 (2)";
            this->fcgtabPageSVTAV1_2->UseVisualStyleBackColor = true;
            // 
            // fcgLBEnableStatReport
            // 
            this->fcgLBEnableStatReport->AutoSize = true;
            this->fcgLBEnableStatReport->Location = System::Drawing::Point(478, 11);
            this->fcgLBEnableStatReport->Name = L"fcgLBEnableStatReport";
            this->fcgLBEnableStatReport->Size = System::Drawing::Size(69, 14);
            this->fcgLBEnableStatReport->TabIndex = 243;
            this->fcgLBEnableStatReport->Text = L"Stat Report";
            // 
            // fcgCBEnableStatReport
            // 
            this->fcgCBEnableStatReport->AutoSize = true;
            this->fcgCBEnableStatReport->Location = System::Drawing::Point(564, 12);
            this->fcgCBEnableStatReport->Name = L"fcgCBEnableStatReport";
            this->fcgCBEnableStatReport->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableStatReport->TabIndex = 170;
            this->fcgCBEnableStatReport->Tag = L"reCmd";
            this->fcgCBEnableStatReport->UseVisualStyleBackColor = true;
            // 
            // fcgLBSTATUS
            // 
            this->fcgLBSTATUS->AutoSize = true;
            this->fcgLBSTATUS->Location = System::Drawing::Point(8, 14);
            this->fcgLBSTATUS->Name = L"fcgLBSTATUS";
            this->fcgLBSTATUS->Size = System::Drawing::Size(78, 14);
            this->fcgLBSTATUS->TabIndex = 236;
            this->fcgLBSTATUS->Text = L"ステータスファイル";
            // 
            // fcgTXStatusFile
            // 
            this->fcgTXStatusFile->Location = System::Drawing::Point(103, 11);
            this->fcgTXStatusFile->Name = L"fcgTXStatusFile";
            this->fcgTXStatusFile->Size = System::Drawing::Size(253, 21);
            this->fcgTXStatusFile->TabIndex = 160;
            this->fcgTXStatusFile->Tag = L"reCmd";
            // 
            // fcgBTStatusFile
            // 
            this->fcgBTStatusFile->Location = System::Drawing::Point(356, 10);
            this->fcgBTStatusFile->Name = L"fcgBTStatusFile";
            this->fcgBTStatusFile->Size = System::Drawing::Size(27, 22);
            this->fcgBTStatusFile->TabIndex = 161;
            this->fcgBTStatusFile->Text = L"...";
            this->fcgBTStatusFile->UseVisualStyleBackColor = true;
            this->fcgBTStatusFile->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTStatusFile_Click);
            // 
            // fcgtabPageExSettings
            // 
            this->fcgtabPageExSettings->Controls->Add(this->fcgBTX264PathSub);
            this->fcgtabPageExSettings->Controls->Add(this->fcgTXX264PathSub);
            this->fcgtabPageExSettings->Controls->Add(this->fcgLBX264PathSub);
            this->fcgtabPageExSettings->Controls->Add(this->fcgLBTempDir);
            this->fcgtabPageExSettings->Controls->Add(this->fcgBTCustomTempDir);
            this->fcgtabPageExSettings->Controls->Add(this->fcggroupBoxCmdEx);
            this->fcgtabPageExSettings->Controls->Add(this->fcgTXCustomTempDir);
            this->fcgtabPageExSettings->Controls->Add(this->fcgCXTempDir);
            this->fcgtabPageExSettings->Controls->Add(this->fcgCXX264Priority);
            this->fcgtabPageExSettings->Controls->Add(this->fcgLBX264Priority);
            this->fcgtabPageExSettings->Controls->Add(this->fcggroupBoxExSettings);
            this->fcgtabPageExSettings->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageExSettings->Name = L"fcgtabPageExSettings";
            this->fcgtabPageExSettings->Size = System::Drawing::Size(608, 518);
            this->fcgtabPageExSettings->TabIndex = 3;
            this->fcgtabPageExSettings->Text = L"拡張";
            this->fcgtabPageExSettings->UseVisualStyleBackColor = true;
            // 
            // fcgBTX264PathSub
            // 
            this->fcgBTX264PathSub->Location = System::Drawing::Point(575, 33);
            this->fcgBTX264PathSub->Name = L"fcgBTX264PathSub";
            this->fcgBTX264PathSub->Size = System::Drawing::Size(27, 22);
            this->fcgBTX264PathSub->TabIndex = 2;
            this->fcgBTX264PathSub->Text = L"...";
            this->fcgBTX264PathSub->UseVisualStyleBackColor = true;
            this->fcgBTX264PathSub->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTX264PathSub_Click);
            // 
            // fcgTXX264PathSub
            // 
            this->fcgTXX264PathSub->AllowDrop = true;
            this->fcgTXX264PathSub->Location = System::Drawing::Point(377, 34);
            this->fcgTXX264PathSub->Name = L"fcgTXX264PathSub";
            this->fcgTXX264PathSub->Size = System::Drawing::Size(194, 21);
            this->fcgTXX264PathSub->TabIndex = 1;
            this->fcgTXX264PathSub->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXX264PathSub_TextChanged);
            this->fcgTXX264PathSub->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXX264PathSub_Enter);
            this->fcgTXX264PathSub->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXX264PathSub_Leave);
            // 
            // fcgLBX264PathSub
            // 
            this->fcgLBX264PathSub->AutoSize = true;
            this->fcgLBX264PathSub->Location = System::Drawing::Point(355, 13);
            this->fcgLBX264PathSub->Name = L"fcgLBX264PathSub";
            this->fcgLBX264PathSub->Size = System::Drawing::Size(49, 14);
            this->fcgLBX264PathSub->TabIndex = 5;
            this->fcgLBX264PathSub->Text = L"～の指定";
            // 
            // fcgLBTempDir
            // 
            this->fcgLBTempDir->AutoSize = true;
            this->fcgLBTempDir->Location = System::Drawing::Point(362, 154);
            this->fcgLBTempDir->Name = L"fcgLBTempDir";
            this->fcgLBTempDir->Size = System::Drawing::Size(60, 14);
            this->fcgLBTempDir->TabIndex = 4;
            this->fcgLBTempDir->Text = L"一時フォルダ";
            // 
            // fcgBTCustomTempDir
            // 
            this->fcgBTCustomTempDir->Location = System::Drawing::Point(562, 207);
            this->fcgBTCustomTempDir->Name = L"fcgBTCustomTempDir";
            this->fcgBTCustomTempDir->Size = System::Drawing::Size(29, 23);
            this->fcgBTCustomTempDir->TabIndex = 6;
            this->fcgBTCustomTempDir->Text = L"...";
            this->fcgBTCustomTempDir->UseVisualStyleBackColor = true;
            this->fcgBTCustomTempDir->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTCustomTempDir_Click);
            // 
            // fcggroupBoxCmdEx
            // 
            this->fcggroupBoxCmdEx->Controls->Add(this->fcgCXCmdExInsert);
            this->fcggroupBoxCmdEx->Controls->Add(this->fcgCBNulOutCLI);
            this->fcggroupBoxCmdEx->Controls->Add(this->fcgBTCmdEx);
            this->fcggroupBoxCmdEx->Controls->Add(this->fcgTXCmdEx);
            this->fcggroupBoxCmdEx->Location = System::Drawing::Point(8, 243);
            this->fcggroupBoxCmdEx->Name = L"fcggroupBoxCmdEx";
            this->fcggroupBoxCmdEx->Size = System::Drawing::Size(589, 233);
            this->fcggroupBoxCmdEx->TabIndex = 7;
            this->fcggroupBoxCmdEx->TabStop = false;
            this->fcggroupBoxCmdEx->Text = L"追加コマンド";
            // 
            // fcgCXCmdExInsert
            // 
            this->fcgCXCmdExInsert->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXCmdExInsert->FormattingEnabled = true;
            this->fcgCXCmdExInsert->Location = System::Drawing::Point(197, 204);
            this->fcgCXCmdExInsert->Name = L"fcgCXCmdExInsert";
            this->fcgCXCmdExInsert->Size = System::Drawing::Size(168, 22);
            this->fcgCXCmdExInsert->TabIndex = 4;
            this->fcgCXCmdExInsert->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfig::fcgCXCmdExInsert_SelectedIndexChanged);
            this->fcgCXCmdExInsert->FontChanged += gcnew System::EventHandler(this, &frmConfig::fcgCXCmdExInsert_FontChanged);
            // 
            // fcgCBNulOutCLI
            // 
            this->fcgCBNulOutCLI->AutoSize = true;
            this->fcgCBNulOutCLI->Location = System::Drawing::Point(18, 206);
            this->fcgCBNulOutCLI->Name = L"fcgCBNulOutCLI";
            this->fcgCBNulOutCLI->Size = System::Drawing::Size(65, 18);
            this->fcgCBNulOutCLI->TabIndex = 2;
            this->fcgCBNulOutCLI->Tag = L"chValue";
            this->fcgCBNulOutCLI->Text = L"nul出力";
            this->fcgCBNulOutCLI->UseVisualStyleBackColor = true;
            // 
            // fcgBTCmdEx
            // 
            this->fcgBTCmdEx->Location = System::Drawing::Point(482, 204);
            this->fcgBTCmdEx->Name = L"fcgBTCmdEx";
            this->fcgBTCmdEx->Size = System::Drawing::Size(97, 23);
            this->fcgBTCmdEx->TabIndex = 1;
            this->fcgBTCmdEx->Text = L"GUI部に反映";
            this->fcgBTCmdEx->UseVisualStyleBackColor = true;
            this->fcgBTCmdEx->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTCmdEx_Click);
            // 
            // fcgTXCmdEx
            // 
            this->fcgTXCmdEx->AllowDrop = true;
            this->fcgTXCmdEx->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgTXCmdEx->Location = System::Drawing::Point(6, 20);
            this->fcgTXCmdEx->Multiline = true;
            this->fcgTXCmdEx->Name = L"fcgTXCmdEx";
            this->fcgTXCmdEx->Size = System::Drawing::Size(577, 180);
            this->fcgTXCmdEx->TabIndex = 0;
            this->fcgTXCmdEx->Tag = L"chValue";
            this->fcgTXCmdEx->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgInsertDragDropFilename_DragDrop);
            this->fcgTXCmdEx->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgInsertDragDropFilename_Enter);
            this->fcgTXCmdEx->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgInsertDragDropFilename_DragOver);
            // 
            // fcgTXCustomTempDir
            // 
            this->fcgTXCustomTempDir->Location = System::Drawing::Point(377, 208);
            this->fcgTXCustomTempDir->Name = L"fcgTXCustomTempDir";
            this->fcgTXCustomTempDir->Size = System::Drawing::Size(182, 21);
            this->fcgTXCustomTempDir->TabIndex = 5;
            this->fcgTXCustomTempDir->Tag = L"";
            this->fcgTXCustomTempDir->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXCustomTempDir_TextChanged);
            // 
            // fcgCXTempDir
            // 
            this->fcgCXTempDir->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXTempDir->FormattingEnabled = true;
            this->fcgCXTempDir->Location = System::Drawing::Point(365, 180);
            this->fcgCXTempDir->Name = L"fcgCXTempDir";
            this->fcgCXTempDir->Size = System::Drawing::Size(209, 22);
            this->fcgCXTempDir->TabIndex = 4;
            this->fcgCXTempDir->Tag = L"chValue";
            // 
            // fcgCXX264Priority
            // 
            this->fcgCXX264Priority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXX264Priority->FormattingEnabled = true;
            this->fcgCXX264Priority->Location = System::Drawing::Point(435, 100);
            this->fcgCXX264Priority->Name = L"fcgCXX264Priority";
            this->fcgCXX264Priority->Size = System::Drawing::Size(152, 22);
            this->fcgCXX264Priority->TabIndex = 3;
            this->fcgCXX264Priority->Tag = L"chValue";
            // 
            // fcgLBX264Priority
            // 
            this->fcgLBX264Priority->AutoSize = true;
            this->fcgLBX264Priority->Location = System::Drawing::Point(362, 103);
            this->fcgLBX264Priority->Name = L"fcgLBX264Priority";
            this->fcgLBX264Priority->Size = System::Drawing::Size(67, 14);
            this->fcgLBX264Priority->TabIndex = 1;
            this->fcgLBX264Priority->Text = L"x264優先度";
            // 
            // fcggroupBoxExSettings
            // 
            this->fcggroupBoxExSettings->Controls->Add(this->fcgCBAuoTcfileout);
            this->fcggroupBoxExSettings->Controls->Add(this->fcgCBAFSBitrateCorrection);
            this->fcggroupBoxExSettings->Controls->Add(this->fcgCBAFS);
            this->fcggroupBoxExSettings->Location = System::Drawing::Point(8, 3);
            this->fcggroupBoxExSettings->Name = L"fcggroupBoxExSettings";
            this->fcggroupBoxExSettings->Size = System::Drawing::Size(323, 234);
            this->fcggroupBoxExSettings->TabIndex = 0;
            this->fcggroupBoxExSettings->TabStop = false;
            this->fcggroupBoxExSettings->Text = L"拡張設定";
            // 
            // fcgCBAuoTcfileout
            // 
            this->fcgCBAuoTcfileout->AutoSize = true;
            this->fcgCBAuoTcfileout->Location = System::Drawing::Point(18, 114);
            this->fcgCBAuoTcfileout->Name = L"fcgCBAuoTcfileout";
            this->fcgCBAuoTcfileout->Size = System::Drawing::Size(98, 18);
            this->fcgCBAuoTcfileout->TabIndex = 3;
            this->fcgCBAuoTcfileout->Tag = L"chValue";
            this->fcgCBAuoTcfileout->Text = L"タイムコード出力";
            this->fcgCBAuoTcfileout->UseVisualStyleBackColor = true;
            // 
            // fcgCBAFSBitrateCorrection
            // 
            this->fcgCBAFSBitrateCorrection->AutoSize = true;
            this->fcgCBAFSBitrateCorrection->Location = System::Drawing::Point(34, 53);
            this->fcgCBAFSBitrateCorrection->Name = L"fcgCBAFSBitrateCorrection";
            this->fcgCBAFSBitrateCorrection->Size = System::Drawing::Size(278, 18);
            this->fcgCBAFSBitrateCorrection->TabIndex = 1;
            this->fcgCBAFSBitrateCorrection->Tag = L"chValue";
            this->fcgCBAFSBitrateCorrection->Text = L"設定したビットレートになるよう補正する(自動マルチパス時)";
            this->fcgCBAFSBitrateCorrection->UseVisualStyleBackColor = true;
            // 
            // fcgCBAFS
            // 
            this->fcgCBAFS->AutoSize = true;
            this->fcgCBAFS->Location = System::Drawing::Point(18, 29);
            this->fcgCBAFS->Name = L"fcgCBAFS";
            this->fcgCBAFS->Size = System::Drawing::Size(183, 18);
            this->fcgCBAFS->TabIndex = 0;
            this->fcgCBAFS->Tag = L"chValue";
            this->fcgCBAFS->Text = L"自動フィールドシフト(afs)を使用する";
            this->fcgCBAFS->UseVisualStyleBackColor = true;
            this->fcgCBAFS->CheckedChanged += gcnew System::EventHandler(this, &frmConfig::fcgCBAFS_CheckedChanged);
            // 
            // fcgCSExeFiles
            // 
            this->fcgCSExeFiles->ImageScalingSize = System::Drawing::Size(18, 18);
            this->fcgCSExeFiles->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fcgTSExeFileshelp });
            this->fcgCSExeFiles->Name = L"fcgCSx264";
            this->fcgCSExeFiles->Size = System::Drawing::Size(131, 26);
            // 
            // fcgTSExeFileshelp
            // 
            this->fcgTSExeFileshelp->Name = L"fcgTSExeFileshelp";
            this->fcgTSExeFileshelp->Size = System::Drawing::Size(130, 22);
            this->fcgTSExeFileshelp->Text = L"helpを表示";
            this->fcgTSExeFileshelp->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSExeFileshelp_Click);
            // 
            // fcgtoolStripSettings
            // 
            this->fcgtoolStripSettings->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgtoolStripSettings->ImageScalingSize = System::Drawing::Size(18, 18);
            this->fcgtoolStripSettings->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(15) {
                this->fcgTSBSave,
                    this->fcgTSBSaveNew, this->fcgTSBDelete, this->fcgtoolStripSeparator1, this->fcgTSSettings, this->fcgTSBCMDOnly, this->toolStripSeparator3,
                    this->fcgTSLanguage, this->toolStripSeparator2, this->fcgTSBBitrateCalc, this->toolStripSeparator5, this->fcgTSBOtherSettings,
                    this->fcgTSLSettingsNotes, this->fcgTSTSettingsNotes, this->toolStripSeparator4
            });
            this->fcgtoolStripSettings->Location = System::Drawing::Point(0, 0);
            this->fcgtoolStripSettings->Name = L"fcgtoolStripSettings";
            this->fcgtoolStripSettings->Padding = System::Windows::Forms::Padding(0);
            this->fcgtoolStripSettings->Size = System::Drawing::Size(1008, 25);
            this->fcgtoolStripSettings->TabIndex = 1;
            this->fcgtoolStripSettings->Text = L"toolStrip1";
            // 
            // fcgTSBSave
            // 
            this->fcgTSBSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSBSave.Image")));
            this->fcgTSBSave->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBSave->Name = L"fcgTSBSave";
            this->fcgTSBSave->Size = System::Drawing::Size(86, 22);
            this->fcgTSBSave->Text = L"上書き保存";
            this->fcgTSBSave->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSBSave_Click);
            // 
            // fcgTSBSaveNew
            // 
            this->fcgTSBSaveNew->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSBSaveNew.Image")));
            this->fcgTSBSaveNew->ImageTransparentColor = System::Drawing::Color::Black;
            this->fcgTSBSaveNew->Name = L"fcgTSBSaveNew";
            this->fcgTSBSaveNew->Size = System::Drawing::Size(77, 22);
            this->fcgTSBSaveNew->Text = L"新規保存";
            this->fcgTSBSaveNew->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSBSaveNew_Click);
            // 
            // fcgTSBDelete
            // 
            this->fcgTSBDelete->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSBDelete.Image")));
            this->fcgTSBDelete->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBDelete->Name = L"fcgTSBDelete";
            this->fcgTSBDelete->Size = System::Drawing::Size(53, 22);
            this->fcgTSBDelete->Text = L"削除";
            this->fcgTSBDelete->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSBDelete_Click);
            // 
            // fcgtoolStripSeparator1
            // 
            this->fcgtoolStripSeparator1->Name = L"fcgtoolStripSeparator1";
            this->fcgtoolStripSeparator1->Size = System::Drawing::Size(6, 25);
            // 
            // fcgTSSettings
            // 
            this->fcgTSSettings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSSettings.Image")));
            this->fcgTSSettings->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSSettings->Name = L"fcgTSSettings";
            this->fcgTSSettings->Size = System::Drawing::Size(79, 22);
            this->fcgTSSettings->Text = L"プリセット";
            this->fcgTSSettings->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &frmConfig::fcgTSSettings_DropDownItemClicked);
            this->fcgTSSettings->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSSettings_Click);
            // 
            // fcgTSBCMDOnly
            // 
            this->fcgTSBCMDOnly->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSBCMDOnly->CheckOnClick = true;
            this->fcgTSBCMDOnly->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSBCMDOnly.Image")));
            this->fcgTSBCMDOnly->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBCMDOnly->Name = L"fcgTSBCMDOnly";
            this->fcgTSBCMDOnly->Size = System::Drawing::Size(76, 22);
            this->fcgTSBCMDOnly->Tag = L"chValue";
            this->fcgTSBCMDOnly->Text = L"CLIモード";
            this->fcgTSBCMDOnly->CheckedChanged += gcnew System::EventHandler(this, &frmConfig::fcgTSBCMDOnly_CheckedChanged);
            // 
            // toolStripSeparator3
            // 
            this->toolStripSeparator3->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->toolStripSeparator3->Name = L"toolStripSeparator3";
            this->toolStripSeparator3->Size = System::Drawing::Size(6, 25);
            // 
            // fcgTSLanguage
            // 
            this->fcgTSLanguage->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSLanguage->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->fcgTSLanguage->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSLanguage.Image")));
            this->fcgTSLanguage->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSLanguage->Name = L"fcgTSLanguage";
            this->fcgTSLanguage->Size = System::Drawing::Size(44, 22);
            this->fcgTSLanguage->Text = L"言語";
            this->fcgTSLanguage->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &frmConfig::fcgTSLanguage_DropDownItemClicked);
            // 
            // toolStripSeparator2
            // 
            this->toolStripSeparator2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->toolStripSeparator2->Name = L"toolStripSeparator2";
            this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
            // 
            // fcgTSBBitrateCalc
            // 
            this->fcgTSBBitrateCalc->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSBBitrateCalc->CheckOnClick = true;
            this->fcgTSBBitrateCalc->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->fcgTSBBitrateCalc->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSBBitrateCalc.Image")));
            this->fcgTSBBitrateCalc->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBBitrateCalc->Name = L"fcgTSBBitrateCalc";
            this->fcgTSBBitrateCalc->Size = System::Drawing::Size(97, 22);
            this->fcgTSBBitrateCalc->Text = L"ビットレート計算機";
            this->fcgTSBBitrateCalc->CheckedChanged += gcnew System::EventHandler(this, &frmConfig::fcgTSBBitrateCalc_CheckedChanged);
            // 
            // toolStripSeparator5
            // 
            this->toolStripSeparator5->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->toolStripSeparator5->Name = L"toolStripSeparator5";
            this->toolStripSeparator5->Size = System::Drawing::Size(6, 25);
            // 
            // fcgTSBOtherSettings
            // 
            this->fcgTSBOtherSettings->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSBOtherSettings->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->fcgTSBOtherSettings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fcgTSBOtherSettings.Image")));
            this->fcgTSBOtherSettings->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBOtherSettings->Name = L"fcgTSBOtherSettings";
            this->fcgTSBOtherSettings->Size = System::Drawing::Size(76, 22);
            this->fcgTSBOtherSettings->Text = L"その他の設定";
            this->fcgTSBOtherSettings->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSBOtherSettings_Click);
            // 
            // fcgTSLSettingsNotes
            // 
            this->fcgTSLSettingsNotes->DoubleClickEnabled = true;
            this->fcgTSLSettingsNotes->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgTSLSettingsNotes->Margin = System::Windows::Forms::Padding(3, 1, 0, 2);
            this->fcgTSLSettingsNotes->Name = L"fcgTSLSettingsNotes";
            this->fcgTSLSettingsNotes->Overflow = System::Windows::Forms::ToolStripItemOverflow::Never;
            this->fcgTSLSettingsNotes->Size = System::Drawing::Size(45, 22);
            this->fcgTSLSettingsNotes->Text = L"メモ表示";
            this->fcgTSLSettingsNotes->DoubleClick += gcnew System::EventHandler(this, &frmConfig::fcgTSLSettingsNotes_DoubleClick);
            // 
            // fcgTSTSettingsNotes
            // 
            this->fcgTSTSettingsNotes->BackColor = System::Drawing::SystemColors::Window;
            this->fcgTSTSettingsNotes->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgTSTSettingsNotes->Margin = System::Windows::Forms::Padding(3, 0, 1, 0);
            this->fcgTSTSettingsNotes->Name = L"fcgTSTSettingsNotes";
            this->fcgTSTSettingsNotes->Size = System::Drawing::Size(161, 25);
            this->fcgTSTSettingsNotes->Text = L"メモ...";
            this->fcgTSTSettingsNotes->Visible = false;
            this->fcgTSTSettingsNotes->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTSTSettingsNotes_Leave);
            this->fcgTSTSettingsNotes->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmConfig::fcgTSTSettingsNotes_KeyDown);
            this->fcgTSTSettingsNotes->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTSTSettingsNotes_TextChanged);
            // 
            // toolStripSeparator4
            // 
            this->toolStripSeparator4->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->toolStripSeparator4->Name = L"toolStripSeparator4";
            this->toolStripSeparator4->Size = System::Drawing::Size(6, 25);
            // 
            // fcgtabControlMux
            // 
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageMP4);
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageMKV);
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageMux);
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageBat);
            this->fcgtabControlMux->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgtabControlMux->Location = System::Drawing::Point(2, 2);
            this->fcgtabControlMux->Name = L"fcgtabControlMux";
            this->fcgtabControlMux->SelectedIndex = 0;
            this->fcgtabControlMux->Size = System::Drawing::Size(384, 239);
            this->fcgtabControlMux->TabIndex = 3;
            // 
            // fcgtabPageMP4
            // 
            this->fcgtabPageMP4->Controls->Add(this->fcgCBMP4MuxApple);
            this->fcgtabPageMP4->Controls->Add(this->fcgBTTC2MP4Path);
            this->fcgtabPageMP4->Controls->Add(this->fcgTXTC2MP4Path);
            this->fcgtabPageMP4->Controls->Add(this->fcgBTMP4MuxerPath);
            this->fcgtabPageMP4->Controls->Add(this->fcgTXMP4MuxerPath);
            this->fcgtabPageMP4->Controls->Add(this->fcgLBTC2MP4Path);
            this->fcgtabPageMP4->Controls->Add(this->fcgLBMP4MuxerPath);
            this->fcgtabPageMP4->Controls->Add(this->fcgCXMP4CmdEx);
            this->fcgtabPageMP4->Controls->Add(this->fcgLBMP4CmdEx);
            this->fcgtabPageMP4->Controls->Add(this->fcgCBMP4MuxerExt);
            this->fcgtabPageMP4->Controls->Add(this->fcgBTMP4RawPath);
            this->fcgtabPageMP4->Controls->Add(this->fcgTXMP4RawPath);
            this->fcgtabPageMP4->Controls->Add(this->fcgLBMP4RawPath);
            this->fcgtabPageMP4->Controls->Add(this->fcgBTMP4BoxTempDir);
            this->fcgtabPageMP4->Controls->Add(this->fcgTXMP4BoxTempDir);
            this->fcgtabPageMP4->Controls->Add(this->fcgCXMP4BoxTempDir);
            this->fcgtabPageMP4->Controls->Add(this->fcgLBMP4BoxTempDir);
            this->fcgtabPageMP4->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageMP4->Name = L"fcgtabPageMP4";
            this->fcgtabPageMP4->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
            this->fcgtabPageMP4->Size = System::Drawing::Size(376, 212);
            this->fcgtabPageMP4->TabIndex = 0;
            this->fcgtabPageMP4->Text = L"mp4";
            this->fcgtabPageMP4->UseVisualStyleBackColor = true;
            // 
            // fcgCBMP4MuxApple
            // 
            this->fcgCBMP4MuxApple->AutoSize = true;
            this->fcgCBMP4MuxApple->Location = System::Drawing::Point(261, 37);
            this->fcgCBMP4MuxApple->Name = L"fcgCBMP4MuxApple";
            this->fcgCBMP4MuxApple->Size = System::Drawing::Size(109, 18);
            this->fcgCBMP4MuxApple->TabIndex = 2;
            this->fcgCBMP4MuxApple->Tag = L"chValue";
            this->fcgCBMP4MuxApple->Text = L"Apple形式に対応";
            this->fcgCBMP4MuxApple->UseVisualStyleBackColor = true;
            // 
            // fcgBTTC2MP4Path
            // 
            this->fcgBTTC2MP4Path->Location = System::Drawing::Point(340, 94);
            this->fcgBTTC2MP4Path->Name = L"fcgBTTC2MP4Path";
            this->fcgBTTC2MP4Path->Size = System::Drawing::Size(30, 23);
            this->fcgBTTC2MP4Path->TabIndex = 6;
            this->fcgBTTC2MP4Path->Text = L"...";
            this->fcgBTTC2MP4Path->UseVisualStyleBackColor = true;
            this->fcgBTTC2MP4Path->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTTC2MP4Path_Click);
            // 
            // fcgTXTC2MP4Path
            // 
            this->fcgTXTC2MP4Path->AllowDrop = true;
            this->fcgTXTC2MP4Path->Location = System::Drawing::Point(145, 95);
            this->fcgTXTC2MP4Path->Name = L"fcgTXTC2MP4Path";
            this->fcgTXTC2MP4Path->Size = System::Drawing::Size(193, 21);
            this->fcgTXTC2MP4Path->TabIndex = 5;
            this->fcgTXTC2MP4Path->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXTC2MP4Path_TextChanged);
            this->fcgTXTC2MP4Path->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXTC2MP4Path->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            this->fcgTXTC2MP4Path->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXTC2MP4Path_Enter);
            this->fcgTXTC2MP4Path->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXTC2MP4Path_Leave);
            // 
            // fcgBTMP4MuxerPath
            // 
            this->fcgBTMP4MuxerPath->Location = System::Drawing::Point(340, 65);
            this->fcgBTMP4MuxerPath->Name = L"fcgBTMP4MuxerPath";
            this->fcgBTMP4MuxerPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTMP4MuxerPath->TabIndex = 4;
            this->fcgBTMP4MuxerPath->Text = L"...";
            this->fcgBTMP4MuxerPath->UseVisualStyleBackColor = true;
            this->fcgBTMP4MuxerPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTMP4MuxerPath_Click);
            // 
            // fcgTXMP4MuxerPath
            // 
            this->fcgTXMP4MuxerPath->AllowDrop = true;
            this->fcgTXMP4MuxerPath->Location = System::Drawing::Point(145, 66);
            this->fcgTXMP4MuxerPath->Name = L"fcgTXMP4MuxerPath";
            this->fcgTXMP4MuxerPath->Size = System::Drawing::Size(193, 21);
            this->fcgTXMP4MuxerPath->TabIndex = 3;
            this->fcgTXMP4MuxerPath->Tag = L"";
            this->fcgTXMP4MuxerPath->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4MuxerPath_TextChanged);
            this->fcgTXMP4MuxerPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXMP4MuxerPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            this->fcgTXMP4MuxerPath->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4MuxerPath_Enter);
            this->fcgTXMP4MuxerPath->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4MuxerPath_Leave);
            // 
            // fcgLBTC2MP4Path
            // 
            this->fcgLBTC2MP4Path->AutoSize = true;
            this->fcgLBTC2MP4Path->Location = System::Drawing::Point(4, 98);
            this->fcgLBTC2MP4Path->Name = L"fcgLBTC2MP4Path";
            this->fcgLBTC2MP4Path->Size = System::Drawing::Size(49, 14);
            this->fcgLBTC2MP4Path->TabIndex = 4;
            this->fcgLBTC2MP4Path->Text = L"～の指定";
            // 
            // fcgLBMP4MuxerPath
            // 
            this->fcgLBMP4MuxerPath->AutoSize = true;
            this->fcgLBMP4MuxerPath->Location = System::Drawing::Point(4, 69);
            this->fcgLBMP4MuxerPath->Name = L"fcgLBMP4MuxerPath";
            this->fcgLBMP4MuxerPath->Size = System::Drawing::Size(49, 14);
            this->fcgLBMP4MuxerPath->TabIndex = 3;
            this->fcgLBMP4MuxerPath->Text = L"～の指定";
            // 
            // fcgCXMP4CmdEx
            // 
            this->fcgCXMP4CmdEx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMP4CmdEx->FormattingEnabled = true;
            this->fcgCXMP4CmdEx->Location = System::Drawing::Point(213, 9);
            this->fcgCXMP4CmdEx->Name = L"fcgCXMP4CmdEx";
            this->fcgCXMP4CmdEx->Size = System::Drawing::Size(157, 22);
            this->fcgCXMP4CmdEx->TabIndex = 1;
            this->fcgCXMP4CmdEx->Tag = L"chValue";
            // 
            // fcgLBMP4CmdEx
            // 
            this->fcgLBMP4CmdEx->AutoSize = true;
            this->fcgLBMP4CmdEx->Location = System::Drawing::Point(139, 12);
            this->fcgLBMP4CmdEx->Name = L"fcgLBMP4CmdEx";
            this->fcgLBMP4CmdEx->Size = System::Drawing::Size(68, 14);
            this->fcgLBMP4CmdEx->TabIndex = 1;
            this->fcgLBMP4CmdEx->Text = L"拡張オプション";
            // 
            // fcgCBMP4MuxerExt
            // 
            this->fcgCBMP4MuxerExt->AutoSize = true;
            this->fcgCBMP4MuxerExt->Location = System::Drawing::Point(10, 11);
            this->fcgCBMP4MuxerExt->Name = L"fcgCBMP4MuxerExt";
            this->fcgCBMP4MuxerExt->Size = System::Drawing::Size(113, 18);
            this->fcgCBMP4MuxerExt->TabIndex = 0;
            this->fcgCBMP4MuxerExt->Tag = L"chValue";
            this->fcgCBMP4MuxerExt->Text = L"外部muxerを使用";
            this->fcgCBMP4MuxerExt->UseVisualStyleBackColor = true;
            // 
            // fcgBTMP4RawPath
            // 
            this->fcgBTMP4RawPath->Location = System::Drawing::Point(340, 109);
            this->fcgBTMP4RawPath->Name = L"fcgBTMP4RawPath";
            this->fcgBTMP4RawPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTMP4RawPath->TabIndex = 8;
            this->fcgBTMP4RawPath->Text = L"...";
            this->fcgBTMP4RawPath->UseVisualStyleBackColor = true;
            this->fcgBTMP4RawPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTMP4RawMuxerPath_Click);
            // 
            // fcgTXMP4RawPath
            // 
            this->fcgTXMP4RawPath->AllowDrop = true;
            this->fcgTXMP4RawPath->Location = System::Drawing::Point(136, 110);
            this->fcgTXMP4RawPath->Name = L"fcgTXMP4RawPath";
            this->fcgTXMP4RawPath->Size = System::Drawing::Size(202, 21);
            this->fcgTXMP4RawPath->TabIndex = 7;
            this->fcgTXMP4RawPath->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4RawMuxerPath_TextChanged);
            this->fcgTXMP4RawPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXMP4RawPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            this->fcgTXMP4RawPath->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4RawPath_Enter);
            this->fcgTXMP4RawPath->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4RawPath_Leave);
            // 
            // fcgLBMP4RawPath
            // 
            this->fcgLBMP4RawPath->AutoSize = true;
            this->fcgLBMP4RawPath->Location = System::Drawing::Point(4, 113);
            this->fcgLBMP4RawPath->Name = L"fcgLBMP4RawPath";
            this->fcgLBMP4RawPath->Size = System::Drawing::Size(49, 14);
            this->fcgLBMP4RawPath->TabIndex = 20;
            this->fcgLBMP4RawPath->Text = L"～の指定";
            // 
            // fcgBTMP4BoxTempDir
            // 
            this->fcgBTMP4BoxTempDir->Location = System::Drawing::Point(340, 159);
            this->fcgBTMP4BoxTempDir->Name = L"fcgBTMP4BoxTempDir";
            this->fcgBTMP4BoxTempDir->Size = System::Drawing::Size(30, 23);
            this->fcgBTMP4BoxTempDir->TabIndex = 11;
            this->fcgBTMP4BoxTempDir->Text = L"...";
            this->fcgBTMP4BoxTempDir->UseVisualStyleBackColor = true;
            this->fcgBTMP4BoxTempDir->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTMP4BoxTempDir_Click);
            // 
            // fcgTXMP4BoxTempDir
            // 
            this->fcgTXMP4BoxTempDir->Location = System::Drawing::Point(107, 160);
            this->fcgTXMP4BoxTempDir->Name = L"fcgTXMP4BoxTempDir";
            this->fcgTXMP4BoxTempDir->Size = System::Drawing::Size(227, 21);
            this->fcgTXMP4BoxTempDir->TabIndex = 10;
            this->fcgTXMP4BoxTempDir->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4BoxTempDir_TextChanged);
            // 
            // fcgCXMP4BoxTempDir
            // 
            this->fcgCXMP4BoxTempDir->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMP4BoxTempDir->FormattingEnabled = true;
            this->fcgCXMP4BoxTempDir->Location = System::Drawing::Point(145, 132);
            this->fcgCXMP4BoxTempDir->Name = L"fcgCXMP4BoxTempDir";
            this->fcgCXMP4BoxTempDir->Size = System::Drawing::Size(206, 22);
            this->fcgCXMP4BoxTempDir->TabIndex = 9;
            this->fcgCXMP4BoxTempDir->Tag = L"chValue";
            // 
            // fcgLBMP4BoxTempDir
            // 
            this->fcgLBMP4BoxTempDir->AutoSize = true;
            this->fcgLBMP4BoxTempDir->Location = System::Drawing::Point(25, 135);
            this->fcgLBMP4BoxTempDir->Name = L"fcgLBMP4BoxTempDir";
            this->fcgLBMP4BoxTempDir->Size = System::Drawing::Size(105, 14);
            this->fcgLBMP4BoxTempDir->TabIndex = 18;
            this->fcgLBMP4BoxTempDir->Text = L"mp4box一時フォルダ";
            // 
            // fcgtabPageMKV
            // 
            this->fcgtabPageMKV->Controls->Add(this->fcgBTMKVMuxerPath);
            this->fcgtabPageMKV->Controls->Add(this->fcgTXMKVMuxerPath);
            this->fcgtabPageMKV->Controls->Add(this->fcgLBMKVMuxerPath);
            this->fcgtabPageMKV->Controls->Add(this->fcgCXMKVCmdEx);
            this->fcgtabPageMKV->Controls->Add(this->fcgLBMKVMuxerCmdEx);
            this->fcgtabPageMKV->Controls->Add(this->fcgCBMKVMuxerExt);
            this->fcgtabPageMKV->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageMKV->Name = L"fcgtabPageMKV";
            this->fcgtabPageMKV->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
            this->fcgtabPageMKV->Size = System::Drawing::Size(376, 212);
            this->fcgtabPageMKV->TabIndex = 1;
            this->fcgtabPageMKV->Text = L"mkv";
            this->fcgtabPageMKV->UseVisualStyleBackColor = true;
            // 
            // fcgBTMKVMuxerPath
            // 
            this->fcgBTMKVMuxerPath->Location = System::Drawing::Point(340, 76);
            this->fcgBTMKVMuxerPath->Name = L"fcgBTMKVMuxerPath";
            this->fcgBTMKVMuxerPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTMKVMuxerPath->TabIndex = 3;
            this->fcgBTMKVMuxerPath->Text = L"...";
            this->fcgBTMKVMuxerPath->UseVisualStyleBackColor = true;
            this->fcgBTMKVMuxerPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTMKVMuxerPath_Click);
            // 
            // fcgTXMKVMuxerPath
            // 
            this->fcgTXMKVMuxerPath->Location = System::Drawing::Point(131, 77);
            this->fcgTXMKVMuxerPath->Name = L"fcgTXMKVMuxerPath";
            this->fcgTXMKVMuxerPath->Size = System::Drawing::Size(207, 21);
            this->fcgTXMKVMuxerPath->TabIndex = 2;
            this->fcgTXMKVMuxerPath->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXMKVMuxerPath_TextChanged);
            this->fcgTXMKVMuxerPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXMKVMuxerPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            this->fcgTXMKVMuxerPath->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXMKVMuxerPath_Enter);
            this->fcgTXMKVMuxerPath->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXMKVMuxerPath_Leave);
            // 
            // fcgLBMKVMuxerPath
            // 
            this->fcgLBMKVMuxerPath->AutoSize = true;
            this->fcgLBMKVMuxerPath->Location = System::Drawing::Point(4, 80);
            this->fcgLBMKVMuxerPath->Name = L"fcgLBMKVMuxerPath";
            this->fcgLBMKVMuxerPath->Size = System::Drawing::Size(49, 14);
            this->fcgLBMKVMuxerPath->TabIndex = 19;
            this->fcgLBMKVMuxerPath->Text = L"～の指定";
            // 
            // fcgCXMKVCmdEx
            // 
            this->fcgCXMKVCmdEx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMKVCmdEx->FormattingEnabled = true;
            this->fcgCXMKVCmdEx->Location = System::Drawing::Point(213, 43);
            this->fcgCXMKVCmdEx->Name = L"fcgCXMKVCmdEx";
            this->fcgCXMKVCmdEx->Size = System::Drawing::Size(157, 22);
            this->fcgCXMKVCmdEx->TabIndex = 1;
            this->fcgCXMKVCmdEx->Tag = L"chValue";
            // 
            // fcgLBMKVMuxerCmdEx
            // 
            this->fcgLBMKVMuxerCmdEx->AutoSize = true;
            this->fcgLBMKVMuxerCmdEx->Location = System::Drawing::Point(139, 46);
            this->fcgLBMKVMuxerCmdEx->Name = L"fcgLBMKVMuxerCmdEx";
            this->fcgLBMKVMuxerCmdEx->Size = System::Drawing::Size(68, 14);
            this->fcgLBMKVMuxerCmdEx->TabIndex = 17;
            this->fcgLBMKVMuxerCmdEx->Text = L"拡張オプション";
            // 
            // fcgCBMKVMuxerExt
            // 
            this->fcgCBMKVMuxerExt->AutoSize = true;
            this->fcgCBMKVMuxerExt->Location = System::Drawing::Point(10, 45);
            this->fcgCBMKVMuxerExt->Name = L"fcgCBMKVMuxerExt";
            this->fcgCBMKVMuxerExt->Size = System::Drawing::Size(113, 18);
            this->fcgCBMKVMuxerExt->TabIndex = 0;
            this->fcgCBMKVMuxerExt->Tag = L"chValue";
            this->fcgCBMKVMuxerExt->Text = L"外部muxerを使用";
            this->fcgCBMKVMuxerExt->UseVisualStyleBackColor = true;
            // 
            // fcgtabPageMux
            // 
            this->fcgtabPageMux->Controls->Add(this->fcgCXMuxPriority);
            this->fcgtabPageMux->Controls->Add(this->fcgLBMuxPriority);
            this->fcgtabPageMux->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageMux->Name = L"fcgtabPageMux";
            this->fcgtabPageMux->Size = System::Drawing::Size(376, 212);
            this->fcgtabPageMux->TabIndex = 2;
            this->fcgtabPageMux->Text = L"Mux共通設定";
            this->fcgtabPageMux->UseVisualStyleBackColor = true;
            // 
            // fcgCXMuxPriority
            // 
            this->fcgCXMuxPriority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMuxPriority->FormattingEnabled = true;
            this->fcgCXMuxPriority->Location = System::Drawing::Point(102, 64);
            this->fcgCXMuxPriority->Name = L"fcgCXMuxPriority";
            this->fcgCXMuxPriority->Size = System::Drawing::Size(198, 22);
            this->fcgCXMuxPriority->TabIndex = 1;
            this->fcgCXMuxPriority->Tag = L"chValue";
            // 
            // fcgLBMuxPriority
            // 
            this->fcgLBMuxPriority->AutoSize = true;
            this->fcgLBMuxPriority->Location = System::Drawing::Point(15, 67);
            this->fcgLBMuxPriority->Name = L"fcgLBMuxPriority";
            this->fcgLBMuxPriority->Size = System::Drawing::Size(62, 14);
            this->fcgLBMuxPriority->TabIndex = 1;
            this->fcgLBMuxPriority->Text = L"Mux優先度";
            // 
            // fcgtabPageBat
            // 
            this->fcgtabPageBat->Controls->Add(this->fcgLBBatAfterString);
            this->fcgtabPageBat->Controls->Add(this->fcgLBBatBeforeString);
            this->fcgtabPageBat->Controls->Add(this->fcgBTBatAfterPath);
            this->fcgtabPageBat->Controls->Add(this->fcgTXBatAfterPath);
            this->fcgtabPageBat->Controls->Add(this->fcgLBBatAfterPath);
            this->fcgtabPageBat->Controls->Add(this->fcgCBWaitForBatAfter);
            this->fcgtabPageBat->Controls->Add(this->fcgCBRunBatAfter);
            this->fcgtabPageBat->Controls->Add(this->fcgPNSeparator);
            this->fcgtabPageBat->Controls->Add(this->fcgBTBatBeforePath);
            this->fcgtabPageBat->Controls->Add(this->fcgTXBatBeforePath);
            this->fcgtabPageBat->Controls->Add(this->fcgLBBatBeforePath);
            this->fcgtabPageBat->Controls->Add(this->fcgCBWaitForBatBefore);
            this->fcgtabPageBat->Controls->Add(this->fcgCBRunBatBefore);
            this->fcgtabPageBat->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageBat->Name = L"fcgtabPageBat";
            this->fcgtabPageBat->Size = System::Drawing::Size(376, 212);
            this->fcgtabPageBat->TabIndex = 3;
            this->fcgtabPageBat->Text = L"エンコ前後バッチ処理";
            this->fcgtabPageBat->UseVisualStyleBackColor = true;
            // 
            // fcgLBBatAfterString
            // 
            this->fcgLBBatAfterString->AutoSize = true;
            this->fcgLBBatAfterString->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Italic | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
            this->fcgLBBatAfterString->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgLBBatAfterString->Location = System::Drawing::Point(304, 113);
            this->fcgLBBatAfterString->Name = L"fcgLBBatAfterString";
            this->fcgLBBatAfterString->Size = System::Drawing::Size(27, 15);
            this->fcgLBBatAfterString->TabIndex = 13;
            this->fcgLBBatAfterString->Text = L" 後& ";
            this->fcgLBBatAfterString->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // fcgLBBatBeforeString
            // 
            this->fcgLBBatBeforeString->AutoSize = true;
            this->fcgLBBatBeforeString->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Italic | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
            this->fcgLBBatBeforeString->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgLBBatBeforeString->Location = System::Drawing::Point(304, 20);
            this->fcgLBBatBeforeString->Name = L"fcgLBBatBeforeString";
            this->fcgLBBatBeforeString->Size = System::Drawing::Size(27, 15);
            this->fcgLBBatBeforeString->TabIndex = 3;
            this->fcgLBBatBeforeString->Text = L" 前& ";
            this->fcgLBBatBeforeString->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // fcgBTBatAfterPath
            // 
            this->fcgBTBatAfterPath->Location = System::Drawing::Point(330, 154);
            this->fcgBTBatAfterPath->Name = L"fcgBTBatAfterPath";
            this->fcgBTBatAfterPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTBatAfterPath->TabIndex = 11;
            this->fcgBTBatAfterPath->Tag = L"chValue";
            this->fcgBTBatAfterPath->Text = L"...";
            this->fcgBTBatAfterPath->UseVisualStyleBackColor = true;
            this->fcgBTBatAfterPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTBatAfterPath_Click);
            // 
            // fcgTXBatAfterPath
            // 
            this->fcgTXBatAfterPath->AllowDrop = true;
            this->fcgTXBatAfterPath->Location = System::Drawing::Point(126, 155);
            this->fcgTXBatAfterPath->Name = L"fcgTXBatAfterPath";
            this->fcgTXBatAfterPath->Size = System::Drawing::Size(202, 21);
            this->fcgTXBatAfterPath->TabIndex = 10;
            this->fcgTXBatAfterPath->Tag = L"chValue";
            this->fcgTXBatAfterPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXBatAfterPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            // 
            // fcgLBBatAfterPath
            // 
            this->fcgLBBatAfterPath->AutoSize = true;
            this->fcgLBBatAfterPath->Location = System::Drawing::Point(40, 158);
            this->fcgLBBatAfterPath->Name = L"fcgLBBatAfterPath";
            this->fcgLBBatAfterPath->Size = System::Drawing::Size(0, 14);
            this->fcgLBBatAfterPath->TabIndex = 9;
            // 
            // fcgCBWaitForBatAfter
            // 
            this->fcgCBWaitForBatAfter->AutoSize = true;
            this->fcgCBWaitForBatAfter->Location = System::Drawing::Point(40, 129);
            this->fcgCBWaitForBatAfter->Name = L"fcgCBWaitForBatAfter";
            this->fcgCBWaitForBatAfter->Size = System::Drawing::Size(150, 18);
            this->fcgCBWaitForBatAfter->TabIndex = 8;
            this->fcgCBWaitForBatAfter->Tag = L"chValue";
            this->fcgCBWaitForBatAfter->Text = L"バッチ処理の終了を待機する";
            this->fcgCBWaitForBatAfter->UseVisualStyleBackColor = true;
            // 
            // fcgCBRunBatAfter
            // 
            this->fcgCBRunBatAfter->AutoSize = true;
            this->fcgCBRunBatAfter->Location = System::Drawing::Point(18, 105);
            this->fcgCBRunBatAfter->Name = L"fcgCBRunBatAfter";
            this->fcgCBRunBatAfter->Size = System::Drawing::Size(179, 18);
            this->fcgCBRunBatAfter->TabIndex = 7;
            this->fcgCBRunBatAfter->Tag = L"chValue";
            this->fcgCBRunBatAfter->Text = L"エンコード終了後、バッチ処理を行う";
            this->fcgCBRunBatAfter->UseVisualStyleBackColor = true;
            // 
            // fcgPNSeparator
            // 
            this->fcgPNSeparator->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->fcgPNSeparator->Location = System::Drawing::Point(18, 94);
            this->fcgPNSeparator->Name = L"fcgPNSeparator";
            this->fcgPNSeparator->Size = System::Drawing::Size(342, 1);
            this->fcgPNSeparator->TabIndex = 6;
            // 
            // fcgBTBatBeforePath
            // 
            this->fcgBTBatBeforePath->Location = System::Drawing::Point(330, 61);
            this->fcgBTBatBeforePath->Name = L"fcgBTBatBeforePath";
            this->fcgBTBatBeforePath->Size = System::Drawing::Size(30, 23);
            this->fcgBTBatBeforePath->TabIndex = 5;
            this->fcgBTBatBeforePath->Tag = L"chValue";
            this->fcgBTBatBeforePath->Text = L"...";
            this->fcgBTBatBeforePath->UseVisualStyleBackColor = true;
            this->fcgBTBatBeforePath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTBatBeforePath_Click);
            // 
            // fcgTXBatBeforePath
            // 
            this->fcgTXBatBeforePath->AllowDrop = true;
            this->fcgTXBatBeforePath->Location = System::Drawing::Point(126, 62);
            this->fcgTXBatBeforePath->Name = L"fcgTXBatBeforePath";
            this->fcgTXBatBeforePath->Size = System::Drawing::Size(202, 21);
            this->fcgTXBatBeforePath->TabIndex = 4;
            this->fcgTXBatBeforePath->Tag = L"chValue";
            this->fcgTXBatBeforePath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXBatBeforePath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            // 
            // fcgLBBatBeforePath
            // 
            this->fcgLBBatBeforePath->AutoSize = true;
            this->fcgLBBatBeforePath->Location = System::Drawing::Point(40, 65);
            this->fcgLBBatBeforePath->Name = L"fcgLBBatBeforePath";
            this->fcgLBBatBeforePath->Size = System::Drawing::Size(0, 14);
            this->fcgLBBatBeforePath->TabIndex = 2;
            // 
            // fcgCBWaitForBatBefore
            // 
            this->fcgCBWaitForBatBefore->AutoSize = true;
            this->fcgCBWaitForBatBefore->Location = System::Drawing::Point(40, 36);
            this->fcgCBWaitForBatBefore->Name = L"fcgCBWaitForBatBefore";
            this->fcgCBWaitForBatBefore->Size = System::Drawing::Size(150, 18);
            this->fcgCBWaitForBatBefore->TabIndex = 1;
            this->fcgCBWaitForBatBefore->Tag = L"chValue";
            this->fcgCBWaitForBatBefore->Text = L"バッチ処理の終了を待機する";
            this->fcgCBWaitForBatBefore->UseVisualStyleBackColor = true;
            // 
            // fcgCBRunBatBefore
            // 
            this->fcgCBRunBatBefore->AutoSize = true;
            this->fcgCBRunBatBefore->Location = System::Drawing::Point(18, 12);
            this->fcgCBRunBatBefore->Name = L"fcgCBRunBatBefore";
            this->fcgCBRunBatBefore->Size = System::Drawing::Size(179, 18);
            this->fcgCBRunBatBefore->TabIndex = 0;
            this->fcgCBRunBatBefore->Tag = L"chValue";
            this->fcgCBRunBatBefore->Text = L"エンコード開始前、バッチ処理を行う";
            this->fcgCBRunBatBefore->UseVisualStyleBackColor = true;
            // 
            // fcgTXCmd
            // 
            this->fcgTXCmd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->fcgTXCmd->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgTXCmd->Location = System::Drawing::Point(9, 573);
            this->fcgTXCmd->Name = L"fcgTXCmd";
            this->fcgTXCmd->ReadOnly = true;
            this->fcgTXCmd->Size = System::Drawing::Size(992, 21);
            this->fcgTXCmd->TabIndex = 4;
            this->fcgTXCmd->DoubleClick += gcnew System::EventHandler(this, &frmConfig::fcgTXCmd_DoubleClick);
            // 
            // fcgBTCancel
            // 
            this->fcgBTCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->fcgBTCancel->Location = System::Drawing::Point(771, 598);
            this->fcgBTCancel->Name = L"fcgBTCancel";
            this->fcgBTCancel->Size = System::Drawing::Size(84, 28);
            this->fcgBTCancel->TabIndex = 5;
            this->fcgBTCancel->Text = L"キャンセル";
            this->fcgBTCancel->UseVisualStyleBackColor = true;
            this->fcgBTCancel->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTCancel_Click);
            // 
            // fcgBTOK
            // 
            this->fcgBTOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->fcgBTOK->Location = System::Drawing::Point(893, 598);
            this->fcgBTOK->Name = L"fcgBTOK";
            this->fcgBTOK->Size = System::Drawing::Size(84, 28);
            this->fcgBTOK->TabIndex = 6;
            this->fcgBTOK->Text = L"OK";
            this->fcgBTOK->UseVisualStyleBackColor = true;
            this->fcgBTOK->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTOK_Click);
            // 
            // fcgBTDefault
            // 
            this->fcgBTDefault->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->fcgBTDefault->Location = System::Drawing::Point(9, 600);
            this->fcgBTDefault->Name = L"fcgBTDefault";
            this->fcgBTDefault->Size = System::Drawing::Size(112, 28);
            this->fcgBTDefault->TabIndex = 7;
            this->fcgBTDefault->Text = L"デフォルト";
            this->fcgBTDefault->UseVisualStyleBackColor = true;
            this->fcgBTDefault->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTDefault_Click);
            // 
            // fcgLBVersionDate
            // 
            this->fcgLBVersionDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->fcgLBVersionDate->AutoSize = true;
            this->fcgLBVersionDate->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgLBVersionDate->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgLBVersionDate->Location = System::Drawing::Point(416, 607);
            this->fcgLBVersionDate->Name = L"fcgLBVersionDate";
            this->fcgLBVersionDate->Size = System::Drawing::Size(49, 15);
            this->fcgLBVersionDate->TabIndex = 8;
            this->fcgLBVersionDate->Text = L"Version";
            // 
            // fcgLBVersion
            // 
            this->fcgLBVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->fcgLBVersion->AutoSize = true;
            this->fcgLBVersion->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgLBVersion->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgLBVersion->Location = System::Drawing::Point(180, 607);
            this->fcgLBVersion->Name = L"fcgLBVersion";
            this->fcgLBVersion->Size = System::Drawing::Size(49, 15);
            this->fcgLBVersion->TabIndex = 9;
            this->fcgLBVersion->Text = L"Version";
            // 
            // fcgOpenFileDialog
            // 
            this->fcgOpenFileDialog->FileName = L"openFileDialog1";
            // 
            // fcgTTX264
            // 
            this->fcgTTX264->AutomaticDelay = 200;
            this->fcgTTX264->AutoPopDelay = 9999;
            this->fcgTTX264->InitialDelay = 200;
            this->fcgTTX264->IsBalloon = true;
            this->fcgTTX264->ReshowDelay = 40;
            this->fcgTTX264->ShowAlways = true;
            this->fcgTTX264->ToolTipTitle = L"SVT-AV1 options...";
            this->fcgTTX264->UseAnimation = false;
            this->fcgTTX264->UseFading = false;
            // 
            // fcgTTEx
            // 
            this->fcgTTEx->AutomaticDelay = 200;
            this->fcgTTEx->AutoPopDelay = 9999;
            this->fcgTTEx->InitialDelay = 200;
            this->fcgTTEx->IsBalloon = true;
            this->fcgTTEx->ReshowDelay = 50;
            this->fcgTTEx->ShowAlways = true;
            this->fcgTTEx->UseAnimation = false;
            this->fcgTTEx->UseFading = false;
            // 
            // fcgTTX264Version
            // 
            this->fcgTTX264Version->AutomaticDelay = 200;
            this->fcgTTX264Version->AutoPopDelay = 10000;
            this->fcgTTX264Version->InitialDelay = 200;
            this->fcgTTX264Version->IsBalloon = true;
            this->fcgTTX264Version->ReshowDelay = 50;
            this->fcgTTX264Version->ToolTipTitle = L"SVT-AV1 バージョン情報...";
            this->fcgTTX264Version->UseAnimation = false;
            this->fcgTTX264Version->UseFading = false;
            // 
            // fcgCSReplaceStrings
            // 
            this->fcgCSReplaceStrings->ImageScalingSize = System::Drawing::Size(18, 18);
            this->fcgCSReplaceStrings->Name = L"fcgCSReplaceStrings";
            this->fcgCSReplaceStrings->Size = System::Drawing::Size(61, 4);
            // 
            // fcgLBguiExBlog
            // 
            this->fcgLBguiExBlog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
            this->fcgLBguiExBlog->AutoSize = true;
            this->fcgLBguiExBlog->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgLBguiExBlog->LinkColor = System::Drawing::Color::Gray;
            this->fcgLBguiExBlog->Location = System::Drawing::Point(623, 607);
            this->fcgLBguiExBlog->Name = L"fcgLBguiExBlog";
            this->fcgLBguiExBlog->Size = System::Drawing::Size(110, 14);
            this->fcgLBguiExBlog->TabIndex = 10;
            this->fcgLBguiExBlog->TabStop = true;
            this->fcgLBguiExBlog->Text = L"svtAV1guiExについて";
            this->fcgLBguiExBlog->VisitedLinkColor = System::Drawing::Color::Gray;
            this->fcgLBguiExBlog->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &frmConfig::fcgLBguiExBlog_LinkClicked);
            // 
            // fcgtabControlAudio
            // 
            this->fcgtabControlAudio->Controls->Add(this->fcgtabPageAudioMain);
            this->fcgtabControlAudio->Controls->Add(this->fcgtabPageAudioOther);
            this->fcgtabControlAudio->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F));
            this->fcgtabControlAudio->Location = System::Drawing::Point(2, 2);
            this->fcgtabControlAudio->Name = L"fcgtabControlAudio";
            this->fcgtabControlAudio->SelectedIndex = 0;
            this->fcgtabControlAudio->Size = System::Drawing::Size(384, 296);
            this->fcgtabControlAudio->TabIndex = 11;
            // 
            // fcgtabPageAudioMain
            // 
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCXAudioDelayCut);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgLBAudioDelayCut);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCBAudioEncTiming);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCXAudioEncTiming);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCXAudioTempDir);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgTXCustomAudioTempDir);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgBTCustomAudioTempDir);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCBAudioUsePipe);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgLBAudioBitrate);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgNUAudioBitrate);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCBAudio2pass);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCXAudioEncMode);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgLBAudioEncMode);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgBTAudioEncoderPath);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgTXAudioEncoderPath);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgLBAudioEncoderPath);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCBAudioOnly);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCBFAWCheck);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgCXAudioEncoder);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgLBAudioEncoder);
            this->fcgtabPageAudioMain->Controls->Add(this->fcgLBAudioTemp);
            this->fcgtabPageAudioMain->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageAudioMain->Name = L"fcgtabPageAudioMain";
            this->fcgtabPageAudioMain->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
            this->fcgtabPageAudioMain->Size = System::Drawing::Size(376, 269);
            this->fcgtabPageAudioMain->TabIndex = 0;
            this->fcgtabPageAudioMain->Text = L"音声";
            this->fcgtabPageAudioMain->UseVisualStyleBackColor = true;
            // 
            // fcgCXAudioDelayCut
            // 
            this->fcgCXAudioDelayCut->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAudioDelayCut->FormattingEnabled = true;
            this->fcgCXAudioDelayCut->Location = System::Drawing::Point(291, 133);
            this->fcgCXAudioDelayCut->Name = L"fcgCXAudioDelayCut";
            this->fcgCXAudioDelayCut->Size = System::Drawing::Size(70, 22);
            this->fcgCXAudioDelayCut->TabIndex = 43;
            this->fcgCXAudioDelayCut->Tag = L"chValue";
            // 
            // fcgLBAudioDelayCut
            // 
            this->fcgLBAudioDelayCut->AutoSize = true;
            this->fcgLBAudioDelayCut->Location = System::Drawing::Point(224, 136);
            this->fcgLBAudioDelayCut->Name = L"fcgLBAudioDelayCut";
            this->fcgLBAudioDelayCut->Size = System::Drawing::Size(60, 14);
            this->fcgLBAudioDelayCut->TabIndex = 54;
            this->fcgLBAudioDelayCut->Text = L"ディレイカット";
            // 
            // fcgCBAudioEncTiming
            // 
            this->fcgCBAudioEncTiming->AutoSize = true;
            this->fcgCBAudioEncTiming->Location = System::Drawing::Point(228, 54);
            this->fcgCBAudioEncTiming->Name = L"fcgCBAudioEncTiming";
            this->fcgCBAudioEncTiming->Size = System::Drawing::Size(40, 14);
            this->fcgCBAudioEncTiming->TabIndex = 53;
            this->fcgCBAudioEncTiming->Text = L"処理順";
            // 
            // fcgCXAudioEncTiming
            // 
            this->fcgCXAudioEncTiming->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAudioEncTiming->FormattingEnabled = true;
            this->fcgCXAudioEncTiming->Location = System::Drawing::Point(286, 51);
            this->fcgCXAudioEncTiming->Name = L"fcgCXAudioEncTiming";
            this->fcgCXAudioEncTiming->Size = System::Drawing::Size(68, 22);
            this->fcgCXAudioEncTiming->TabIndex = 52;
            this->fcgCXAudioEncTiming->Tag = L"chValue";
            // 
            // fcgCXAudioTempDir
            // 
            this->fcgCXAudioTempDir->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAudioTempDir->FormattingEnabled = true;
            this->fcgCXAudioTempDir->Location = System::Drawing::Point(135, 208);
            this->fcgCXAudioTempDir->Name = L"fcgCXAudioTempDir";
            this->fcgCXAudioTempDir->Size = System::Drawing::Size(150, 22);
            this->fcgCXAudioTempDir->TabIndex = 46;
            this->fcgCXAudioTempDir->Tag = L"chValue";
            // 
            // fcgTXCustomAudioTempDir
            // 
            this->fcgTXCustomAudioTempDir->Location = System::Drawing::Point(64, 236);
            this->fcgTXCustomAudioTempDir->Name = L"fcgTXCustomAudioTempDir";
            this->fcgTXCustomAudioTempDir->Size = System::Drawing::Size(245, 21);
            this->fcgTXCustomAudioTempDir->TabIndex = 47;
            this->fcgTXCustomAudioTempDir->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXCustomAudioTempDir_TextChanged);
            // 
            // fcgBTCustomAudioTempDir
            // 
            this->fcgBTCustomAudioTempDir->Location = System::Drawing::Point(316, 234);
            this->fcgBTCustomAudioTempDir->Name = L"fcgBTCustomAudioTempDir";
            this->fcgBTCustomAudioTempDir->Size = System::Drawing::Size(29, 23);
            this->fcgBTCustomAudioTempDir->TabIndex = 49;
            this->fcgBTCustomAudioTempDir->Text = L"...";
            this->fcgBTCustomAudioTempDir->UseVisualStyleBackColor = true;
            this->fcgBTCustomAudioTempDir->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTCustomAudioTempDir_Click);
            // 
            // fcgCBAudioUsePipe
            // 
            this->fcgCBAudioUsePipe->AutoSize = true;
            this->fcgCBAudioUsePipe->Location = System::Drawing::Point(130, 134);
            this->fcgCBAudioUsePipe->Name = L"fcgCBAudioUsePipe";
            this->fcgCBAudioUsePipe->Size = System::Drawing::Size(73, 18);
            this->fcgCBAudioUsePipe->TabIndex = 42;
            this->fcgCBAudioUsePipe->Tag = L"chValue";
            this->fcgCBAudioUsePipe->Text = L"パイプ処理";
            this->fcgCBAudioUsePipe->UseVisualStyleBackColor = true;
            // 
            // fcgLBAudioBitrate
            // 
            this->fcgLBAudioBitrate->AutoSize = true;
            this->fcgLBAudioBitrate->Location = System::Drawing::Point(284, 161);
            this->fcgLBAudioBitrate->Name = L"fcgLBAudioBitrate";
            this->fcgLBAudioBitrate->Size = System::Drawing::Size(32, 14);
            this->fcgLBAudioBitrate->TabIndex = 50;
            this->fcgLBAudioBitrate->Text = L"kbps";
            // 
            // fcgNUAudioBitrate
            // 
            this->fcgNUAudioBitrate->Location = System::Drawing::Point(212, 157);
            this->fcgNUAudioBitrate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1536, 0, 0, 0 });
            this->fcgNUAudioBitrate->Name = L"fcgNUAudioBitrate";
            this->fcgNUAudioBitrate->Size = System::Drawing::Size(65, 21);
            this->fcgNUAudioBitrate->TabIndex = 40;
            this->fcgNUAudioBitrate->Tag = L"chValue";
            this->fcgNUAudioBitrate->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCBAudio2pass
            // 
            this->fcgCBAudio2pass->AutoSize = true;
            this->fcgCBAudio2pass->Location = System::Drawing::Point(59, 134);
            this->fcgCBAudio2pass->Name = L"fcgCBAudio2pass";
            this->fcgCBAudio2pass->Size = System::Drawing::Size(56, 18);
            this->fcgCBAudio2pass->TabIndex = 41;
            this->fcgCBAudio2pass->Tag = L"chValue";
            this->fcgCBAudio2pass->Text = L"2pass";
            this->fcgCBAudio2pass->UseVisualStyleBackColor = true;
            this->fcgCBAudio2pass->CheckedChanged += gcnew System::EventHandler(this, &frmConfig::fcgCBAudio2pass_CheckedChanged);
            // 
            // fcgCXAudioEncMode
            // 
            this->fcgCXAudioEncMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAudioEncMode->FormattingEnabled = true;
            this->fcgCXAudioEncMode->Location = System::Drawing::Point(16, 156);
            this->fcgCXAudioEncMode->Name = L"fcgCXAudioEncMode";
            this->fcgCXAudioEncMode->Size = System::Drawing::Size(189, 22);
            this->fcgCXAudioEncMode->TabIndex = 39;
            this->fcgCXAudioEncMode->Tag = L"chValue";
            this->fcgCXAudioEncMode->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfig::fcgCXAudioEncMode_SelectedIndexChanged);
            // 
            // fcgLBAudioEncMode
            // 
            this->fcgLBAudioEncMode->AutoSize = true;
            this->fcgLBAudioEncMode->Location = System::Drawing::Point(4, 136);
            this->fcgLBAudioEncMode->Name = L"fcgLBAudioEncMode";
            this->fcgLBAudioEncMode->Size = System::Drawing::Size(32, 14);
            this->fcgLBAudioEncMode->TabIndex = 48;
            this->fcgLBAudioEncMode->Text = L"モード";
            // 
            // fcgBTAudioEncoderPath
            // 
            this->fcgBTAudioEncoderPath->Location = System::Drawing::Point(324, 90);
            this->fcgBTAudioEncoderPath->Name = L"fcgBTAudioEncoderPath";
            this->fcgBTAudioEncoderPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTAudioEncoderPath->TabIndex = 38;
            this->fcgBTAudioEncoderPath->Text = L"...";
            this->fcgBTAudioEncoderPath->UseVisualStyleBackColor = true;
            this->fcgBTAudioEncoderPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTAudioEncoderPath_Click);
            // 
            // fcgTXAudioEncoderPath
            // 
            this->fcgTXAudioEncoderPath->AllowDrop = true;
            this->fcgTXAudioEncoderPath->Location = System::Drawing::Point(16, 92);
            this->fcgTXAudioEncoderPath->Name = L"fcgTXAudioEncoderPath";
            this->fcgTXAudioEncoderPath->Size = System::Drawing::Size(303, 21);
            this->fcgTXAudioEncoderPath->TabIndex = 37;
            this->fcgTXAudioEncoderPath->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXAudioEncoderPath_TextChanged);
            this->fcgTXAudioEncoderPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXAudioEncoderPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            this->fcgTXAudioEncoderPath->Enter += gcnew System::EventHandler(this, &frmConfig::fcgTXAudioEncoderPath_Enter);
            this->fcgTXAudioEncoderPath->Leave += gcnew System::EventHandler(this, &frmConfig::fcgTXAudioEncoderPath_Leave);
            // 
            // fcgLBAudioEncoderPath
            // 
            this->fcgLBAudioEncoderPath->AutoSize = true;
            this->fcgLBAudioEncoderPath->Location = System::Drawing::Point(12, 75);
            this->fcgLBAudioEncoderPath->Name = L"fcgLBAudioEncoderPath";
            this->fcgLBAudioEncoderPath->Size = System::Drawing::Size(49, 14);
            this->fcgLBAudioEncoderPath->TabIndex = 44;
            this->fcgLBAudioEncoderPath->Text = L"～の指定";
            // 
            // fcgCBAudioOnly
            // 
            this->fcgCBAudioOnly->AutoSize = true;
            this->fcgCBAudioOnly->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgCBAudioOnly->Location = System::Drawing::Point(252, 5);
            this->fcgCBAudioOnly->Name = L"fcgCBAudioOnly";
            this->fcgCBAudioOnly->Size = System::Drawing::Size(89, 18);
            this->fcgCBAudioOnly->TabIndex = 34;
            this->fcgCBAudioOnly->Tag = L"chValue";
            this->fcgCBAudioOnly->Text = L"音声のみ出力";
            this->fcgCBAudioOnly->UseVisualStyleBackColor = true;
            // 
            // fcgCBFAWCheck
            // 
            this->fcgCBFAWCheck->AutoSize = true;
            this->fcgCBFAWCheck->Location = System::Drawing::Point(252, 28);
            this->fcgCBFAWCheck->Name = L"fcgCBFAWCheck";
            this->fcgCBFAWCheck->Size = System::Drawing::Size(81, 18);
            this->fcgCBFAWCheck->TabIndex = 36;
            this->fcgCBFAWCheck->Tag = L"chValue";
            this->fcgCBFAWCheck->Text = L"FAWCheck";
            this->fcgCBFAWCheck->UseVisualStyleBackColor = true;
            // 
            // fcgCXAudioEncoder
            // 
            this->fcgCXAudioEncoder->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAudioEncoder->FormattingEnabled = true;
            this->fcgCXAudioEncoder->Location = System::Drawing::Point(17, 34);
            this->fcgCXAudioEncoder->Name = L"fcgCXAudioEncoder";
            this->fcgCXAudioEncoder->Size = System::Drawing::Size(172, 22);
            this->fcgCXAudioEncoder->TabIndex = 32;
            this->fcgCXAudioEncoder->Tag = L"chValue";
            this->fcgCXAudioEncoder->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfig::fcgCXAudioEncoder_SelectedIndexChanged);
            // 
            // fcgLBAudioEncoder
            // 
            this->fcgLBAudioEncoder->AutoSize = true;
            this->fcgLBAudioEncoder->Location = System::Drawing::Point(5, 14);
            this->fcgLBAudioEncoder->Name = L"fcgLBAudioEncoder";
            this->fcgLBAudioEncoder->Size = System::Drawing::Size(48, 14);
            this->fcgLBAudioEncoder->TabIndex = 33;
            this->fcgLBAudioEncoder->Text = L"エンコーダ";
            // 
            // fcgLBAudioTemp
            // 
            this->fcgLBAudioTemp->AutoSize = true;
            this->fcgLBAudioTemp->Location = System::Drawing::Point(7, 211);
            this->fcgLBAudioTemp->Name = L"fcgLBAudioTemp";
            this->fcgLBAudioTemp->Size = System::Drawing::Size(114, 14);
            this->fcgLBAudioTemp->TabIndex = 51;
            this->fcgLBAudioTemp->Text = L"音声一時ファイル出力先";
            // 
            // fcgtabPageAudioOther
            // 
            this->fcgtabPageAudioOther->Controls->Add(this->panel2);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgLBBatAfterAudioString);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgLBBatBeforeAudioString);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgBTBatAfterAudioPath);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgTXBatAfterAudioPath);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgLBBatAfterAudioPath);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgCBRunBatAfterAudio);
            this->fcgtabPageAudioOther->Controls->Add(this->panel1);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgBTBatBeforeAudioPath);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgTXBatBeforeAudioPath);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgLBBatBeforeAudioPath);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgCBRunBatBeforeAudio);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgCXAudioPriority);
            this->fcgtabPageAudioOther->Controls->Add(this->fcgLBAudioPriority);
            this->fcgtabPageAudioOther->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageAudioOther->Name = L"fcgtabPageAudioOther";
            this->fcgtabPageAudioOther->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
            this->fcgtabPageAudioOther->Size = System::Drawing::Size(376, 269);
            this->fcgtabPageAudioOther->TabIndex = 1;
            this->fcgtabPageAudioOther->Text = L"その他";
            this->fcgtabPageAudioOther->UseVisualStyleBackColor = true;
            // 
            // panel2
            // 
            this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel2->Location = System::Drawing::Point(18, 126);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(342, 1);
            this->panel2->TabIndex = 61;
            // 
            // fcgLBBatAfterAudioString
            // 
            this->fcgLBBatAfterAudioString->AutoSize = true;
            this->fcgLBBatAfterAudioString->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Italic | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
            this->fcgLBBatAfterAudioString->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgLBBatAfterAudioString->Location = System::Drawing::Point(304, 208);
            this->fcgLBBatAfterAudioString->Name = L"fcgLBBatAfterAudioString";
            this->fcgLBBatAfterAudioString->Size = System::Drawing::Size(27, 15);
            this->fcgLBBatAfterAudioString->TabIndex = 60;
            this->fcgLBBatAfterAudioString->Text = L" 後& ";
            this->fcgLBBatAfterAudioString->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // fcgLBBatBeforeAudioString
            // 
            this->fcgLBBatBeforeAudioString->AutoSize = true;
            this->fcgLBBatBeforeAudioString->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Italic | System::Drawing::FontStyle::Underline)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
            this->fcgLBBatBeforeAudioString->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
            this->fcgLBBatBeforeAudioString->Location = System::Drawing::Point(304, 139);
            this->fcgLBBatBeforeAudioString->Name = L"fcgLBBatBeforeAudioString";
            this->fcgLBBatBeforeAudioString->Size = System::Drawing::Size(27, 15);
            this->fcgLBBatBeforeAudioString->TabIndex = 51;
            this->fcgLBBatBeforeAudioString->Text = L" 前& ";
            this->fcgLBBatBeforeAudioString->TextAlign = System::Drawing::ContentAlignment::TopCenter;
            // 
            // fcgBTBatAfterAudioPath
            // 
            this->fcgBTBatAfterAudioPath->Location = System::Drawing::Point(330, 231);
            this->fcgBTBatAfterAudioPath->Name = L"fcgBTBatAfterAudioPath";
            this->fcgBTBatAfterAudioPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTBatAfterAudioPath->TabIndex = 59;
            this->fcgBTBatAfterAudioPath->Tag = L"chValue";
            this->fcgBTBatAfterAudioPath->Text = L"...";
            this->fcgBTBatAfterAudioPath->UseVisualStyleBackColor = true;
            this->fcgBTBatAfterAudioPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTBatAfterAudioPath_Click);
            // 
            // fcgTXBatAfterAudioPath
            // 
            this->fcgTXBatAfterAudioPath->AllowDrop = true;
            this->fcgTXBatAfterAudioPath->Location = System::Drawing::Point(126, 232);
            this->fcgTXBatAfterAudioPath->Name = L"fcgTXBatAfterAudioPath";
            this->fcgTXBatAfterAudioPath->Size = System::Drawing::Size(202, 21);
            this->fcgTXBatAfterAudioPath->TabIndex = 58;
            this->fcgTXBatAfterAudioPath->Tag = L"chValue";
            this->fcgTXBatAfterAudioPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXBatAfterAudioPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            // 
            // fcgLBBatAfterAudioPath
            // 
            this->fcgLBBatAfterAudioPath->AutoSize = true;
            this->fcgLBBatAfterAudioPath->Location = System::Drawing::Point(40, 236);
            this->fcgLBBatAfterAudioPath->Name = L"fcgLBBatAfterAudioPath";
            this->fcgLBBatAfterAudioPath->Size = System::Drawing::Size(0, 14);
            this->fcgLBBatAfterAudioPath->TabIndex = 57;
            // 
            // fcgCBRunBatAfterAudio
            // 
            this->fcgCBRunBatAfterAudio->AutoSize = true;
            this->fcgCBRunBatAfterAudio->Location = System::Drawing::Point(18, 207);
            this->fcgCBRunBatAfterAudio->Name = L"fcgCBRunBatAfterAudio";
            this->fcgCBRunBatAfterAudio->Size = System::Drawing::Size(201, 18);
            this->fcgCBRunBatAfterAudio->TabIndex = 55;
            this->fcgCBRunBatAfterAudio->Tag = L"chValue";
            this->fcgCBRunBatAfterAudio->Text = L"音声エンコード終了後、バッチ処理を行う";
            this->fcgCBRunBatAfterAudio->UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Location = System::Drawing::Point(18, 196);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(342, 1);
            this->panel1->TabIndex = 54;
            // 
            // fcgBTBatBeforeAudioPath
            // 
            this->fcgBTBatBeforeAudioPath->Location = System::Drawing::Point(330, 164);
            this->fcgBTBatBeforeAudioPath->Name = L"fcgBTBatBeforeAudioPath";
            this->fcgBTBatBeforeAudioPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTBatBeforeAudioPath->TabIndex = 53;
            this->fcgBTBatBeforeAudioPath->Tag = L"chValue";
            this->fcgBTBatBeforeAudioPath->Text = L"...";
            this->fcgBTBatBeforeAudioPath->UseVisualStyleBackColor = true;
            this->fcgBTBatBeforeAudioPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTBatBeforeAudioPath_Click);
            // 
            // fcgTXBatBeforeAudioPath
            // 
            this->fcgTXBatBeforeAudioPath->AllowDrop = true;
            this->fcgTXBatBeforeAudioPath->Location = System::Drawing::Point(126, 164);
            this->fcgTXBatBeforeAudioPath->Name = L"fcgTXBatBeforeAudioPath";
            this->fcgTXBatBeforeAudioPath->Size = System::Drawing::Size(202, 21);
            this->fcgTXBatBeforeAudioPath->TabIndex = 52;
            this->fcgTXBatBeforeAudioPath->Tag = L"chValue";
            this->fcgTXBatBeforeAudioPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXBatBeforeAudioPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            // 
            // fcgLBBatBeforeAudioPath
            // 
            this->fcgLBBatBeforeAudioPath->AutoSize = true;
            this->fcgLBBatBeforeAudioPath->Location = System::Drawing::Point(40, 167);
            this->fcgLBBatBeforeAudioPath->Name = L"fcgLBBatBeforeAudioPath";
            this->fcgLBBatBeforeAudioPath->Size = System::Drawing::Size(0, 14);
            this->fcgLBBatBeforeAudioPath->TabIndex = 50;
            // 
            // fcgCBRunBatBeforeAudio
            // 
            this->fcgCBRunBatBeforeAudio->AutoSize = true;
            this->fcgCBRunBatBeforeAudio->Location = System::Drawing::Point(18, 139);
            this->fcgCBRunBatBeforeAudio->Name = L"fcgCBRunBatBeforeAudio";
            this->fcgCBRunBatBeforeAudio->Size = System::Drawing::Size(201, 18);
            this->fcgCBRunBatBeforeAudio->TabIndex = 48;
            this->fcgCBRunBatBeforeAudio->Tag = L"chValue";
            this->fcgCBRunBatBeforeAudio->Text = L"音声エンコード開始前、バッチ処理を行う";
            this->fcgCBRunBatBeforeAudio->UseVisualStyleBackColor = true;
            // 
            // fcgCXAudioPriority
            // 
            this->fcgCXAudioPriority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAudioPriority->FormattingEnabled = true;
            this->fcgCXAudioPriority->Location = System::Drawing::Point(156, 20);
            this->fcgCXAudioPriority->Name = L"fcgCXAudioPriority";
            this->fcgCXAudioPriority->Size = System::Drawing::Size(136, 22);
            this->fcgCXAudioPriority->TabIndex = 47;
            this->fcgCXAudioPriority->Tag = L"chValue";
            // 
            // fcgLBAudioPriority
            // 
            this->fcgLBAudioPriority->AutoSize = true;
            this->fcgLBAudioPriority->Location = System::Drawing::Point(29, 23);
            this->fcgLBAudioPriority->Name = L"fcgLBAudioPriority";
            this->fcgLBAudioPriority->Size = System::Drawing::Size(62, 14);
            this->fcgLBAudioPriority->TabIndex = 46;
            this->fcgLBAudioPriority->Text = L"音声優先度";
            // 
            // fcgPNHideTabControlVideo
            // 
            this->fcgPNHideTabControlVideo->Controls->Add(this->fcgtabControlVideo);
            this->fcgPNHideTabControlVideo->Location = System::Drawing::Point(0, 25);
            this->fcgPNHideTabControlVideo->Name = L"fcgPNHideTabControlVideo";
            this->fcgPNHideTabControlVideo->Size = System::Drawing::Size(620, 549);
            this->fcgPNHideTabControlVideo->TabIndex = 12;
            // 
            // fcgPNHideTabControlAudio
            // 
            this->fcgPNHideTabControlAudio->Controls->Add(this->fcgtabControlAudio);
            this->fcgPNHideTabControlAudio->Location = System::Drawing::Point(619, 25);
            this->fcgPNHideTabControlAudio->Name = L"fcgPNHideTabControlAudio";
            this->fcgPNHideTabControlAudio->Size = System::Drawing::Size(388, 300);
            this->fcgPNHideTabControlAudio->TabIndex = 13;
            // 
            // fcgPNHideTabControlMux
            // 
            this->fcgPNHideTabControlMux->Controls->Add(this->fcgtabControlMux);
            this->fcgPNHideTabControlMux->Location = System::Drawing::Point(619, 331);
            this->fcgPNHideTabControlMux->Name = L"fcgPNHideTabControlMux";
            this->fcgPNHideTabControlMux->Size = System::Drawing::Size(388, 243);
            this->fcgPNHideTabControlMux->TabIndex = 14;
            // 
            // fcgPNHideToolStripBorder
            // 
            this->fcgPNHideToolStripBorder->Location = System::Drawing::Point(0, 22);
            this->fcgPNHideToolStripBorder->Name = L"fcgPNHideToolStripBorder";
            this->fcgPNHideToolStripBorder->Size = System::Drawing::Size(1020, 4);
            this->fcgPNHideToolStripBorder->TabIndex = 16;
            this->fcgPNHideToolStripBorder->Visible = false;
            // 
            // frmConfig
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
            this->ClientSize = System::Drawing::Size(1008, 629);
            this->Controls->Add(this->fcgPNHideToolStripBorder);
            this->Controls->Add(this->fcgPNHideTabControlMux);
            this->Controls->Add(this->fcgPNHideTabControlAudio);
            this->Controls->Add(this->fcgPNHideTabControlVideo);
            this->Controls->Add(this->fcgLBguiExBlog);
            this->Controls->Add(this->fcgLBVersion);
            this->Controls->Add(this->fcgLBVersionDate);
            this->Controls->Add(this->fcgBTDefault);
            this->Controls->Add(this->fcgBTOK);
            this->Controls->Add(this->fcgBTCancel);
            this->Controls->Add(this->fcgTXCmd);
            this->Controls->Add(this->fcgtoolStripSettings);
            this->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->Name = L"frmConfig";
            this->ShowIcon = false;
            this->Text = L"Aviutl 出力 プラグイン";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &frmConfig::frmConfig_FormClosing);
            this->Load += gcnew System::EventHandler(this, &frmConfig::frmConfig_Load);
            this->fcgtabControlVideo->ResumeLayout(false);
            this->fcgtabPageSVTAV1_1->ResumeLayout(false);
            this->fcgtabPageSVTAV1_1->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUEnableTF))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUTFStrength))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUVarianceOctile))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNULumaQPBias))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUSharpness))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUVarianceBoostStrength))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNULookahead))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUOverShootPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUUnderShootPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMaxSectionPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMinSectionPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUFilmGrain))->EndInit();
            this->fcggroupBoxColorMatrix->ResumeLayout(false);
            this->fcggroupBoxColorMatrix->PerformLayout();
            this->fcgGroupBoxAspectRatio->ResumeLayout(false);
            this->fcgGroupBoxAspectRatio->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUAspectRatioY))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUAspectRatioX))->EndInit();
            this->fcgPNX264Mode->ResumeLayout(false);
            this->fcgPNX264Mode->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUBitrate))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUQP))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMaxQP))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUMinQP))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUTileColumns))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUTileRows))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUIntraRefreshType))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUKeyint))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUThreads))->EndInit();
            this->fcgtabPageSVTAV1_2->ResumeLayout(false);
            this->fcgtabPageSVTAV1_2->PerformLayout();
            this->fcgtabPageExSettings->ResumeLayout(false);
            this->fcgtabPageExSettings->PerformLayout();
            this->fcggroupBoxCmdEx->ResumeLayout(false);
            this->fcggroupBoxCmdEx->PerformLayout();
            this->fcggroupBoxExSettings->ResumeLayout(false);
            this->fcggroupBoxExSettings->PerformLayout();
            this->fcgCSExeFiles->ResumeLayout(false);
            this->fcgtoolStripSettings->ResumeLayout(false);
            this->fcgtoolStripSettings->PerformLayout();
            this->fcgtabControlMux->ResumeLayout(false);
            this->fcgtabPageMP4->ResumeLayout(false);
            this->fcgtabPageMP4->PerformLayout();
            this->fcgtabPageMKV->ResumeLayout(false);
            this->fcgtabPageMKV->PerformLayout();
            this->fcgtabPageMux->ResumeLayout(false);
            this->fcgtabPageMux->PerformLayout();
            this->fcgtabPageBat->ResumeLayout(false);
            this->fcgtabPageBat->PerformLayout();
            this->fcgtabControlAudio->ResumeLayout(false);
            this->fcgtabPageAudioMain->ResumeLayout(false);
            this->fcgtabPageAudioMain->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fcgNUAudioBitrate))->EndInit();
            this->fcgtabPageAudioOther->ResumeLayout(false);
            this->fcgtabPageAudioOther->PerformLayout();
            this->fcgPNHideTabControlVideo->ResumeLayout(false);
            this->fcgPNHideTabControlAudio->ResumeLayout(false);
            this->fcgPNHideTabControlMux->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        const SYSTEM_DATA *sys_dat;
        std::vector<tstring> *list_lng;
        CONF_GUIEX *conf;
        LocalSettings LocalStg;
        DarkenWindowStgReader *dwStgReader;
        AuoTheme themeMode;
        TBValueBitrateConvert TBBConvert;
        System::Threading::Timer^ qualityTimer;
        int timerChangeValue;
        bool CurrentPipeEnabled;
        bool stgChanged;
        String^ CurrentStgDir;
        ToolStripMenuItem^ CheckedStgMenuItem;
        CONF_GUIEX *cnf_stgSelected;
        String^ lastQualityStr;
    private:
        System::Void CheckTheme();
        System::Void SetAllMouseMove(Control ^top, const AuoTheme themeTo);
        System::Void fcgMouseEnter_SetColor(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgMouseLeave_SetColor(System::Object^  sender, System::EventArgs^  e);
        System::Void TabControl_DarkDrawItem(System::Object^ sender, DrawItemEventArgs^ e);

        System::Void LoadLangText();
        System::Int32 GetCurrentAudioDefaultBitrate();
        delegate System::Void qualityTimerChangeDelegate();
        System::Void InitComboBox();
        System::Void setAudioExtDisplay();
        System::Void AudioEncodeModeChanged();
        System::Void InitStgFileList();
        System::Void RebuildStgFileDropDown(String^ stgDir);
        System::Void RebuildStgFileDropDown(ToolStripDropDownItem^ TS, String^ dir);
        System::Void SetLocalStg();
        System::Void LoadLocalStg();
        System::Void SaveLocalStg();
        System::Boolean CheckLocalStg();
        System::Void SetTXMaxLen(TextBox^ TX, int max_len);
        System::Void SetTXMaxLenAll();
        System::Void InitForm();
        System::Void ConfToFrm(CONF_GUIEX *cnf, bool all);
        String^ FrmToConf(CONF_GUIEX *cnf);
        System::Void SetChangedEvent(Control^ control, System::EventHandler^ _event);
        System::Void SetToolStripEvents(ToolStrip^ TS, System::Windows::Forms::MouseEventHandler^ _event);
        System::Void SetAllCheckChangedEvents(Control ^top);
        System::Void SaveToStgFile(String^ stgName);
        System::Void DeleteStgFile(ToolStripMenuItem^ mItem);
        System::Boolean EnableSettingsNoteChange(bool Enable);
        System::Void fcgTSLSettingsNotes_DoubleClick(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSTSettingsNotes_Leave(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSTSettingsNotes_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
        System::Void fcgTSTSettingsNotes_TextChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void GetfcgTSLSettingsNotes(TCHAR *notes, int nSize);
        System::Void SetfcgTSLSettingsNotes(const TCHAR *notes);
        System::Void SetfcgTSLSettingsNotes(String^ notes);
        System::Void fcgTSBSave_Click(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSBSaveNew_Click(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSBDelete_Click(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSSettings_DropDownItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e);
        System::Void UncheckAllDropDownItem(ToolStripItem^ mItem);
        ToolStripMenuItem^ fcgTSSettingsSearchItem(String^ stgPath, ToolStripItem^ mItem);
        ToolStripMenuItem^ fcgTSSettingsSearchItem(String^ stgPath);
        System::Void CheckTSSettingsDropDownItem(ToolStripMenuItem^ mItem);
        System::Void CheckTSItemsEnabled(CONF_GUIEX *current_conf);

        System::Void InitLangList();
        System::Void SaveSelectedLanguage(const TCHAR *language_text);
        System::Void SetSelectedLanguage(const TCHAR *language_text);
        System::Void CheckTSLanguageDropDownItem(ToolStripMenuItem^ mItem);
        System::Void fcgTSLanguage_DropDownItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e);

        System::Void SetHelpToolTips();
        System::Void SetHelpToolTipsColorMatrix(Control^ control, const char *type);
        System::Void SetX264VersionToolTip(String^ x264Path);
        System::Void ShowExehelp(String^ ExePath, String^ args);
        System::Void fcgTSBOtherSettings_Click(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgChangeEnabled(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgChangeMuxerVisible(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSBBitrateCalc_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void CloseBitrateCalc();
        System::Void SetfbcBTABEnable(bool enable, int max);
        System::Void SetfbcBTVBEnable(bool enable);
        System::Void fcgTSBCMDOnly_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgCBAudio2pass_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgCBAFS_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgCXAudioEncoder_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgCXAudioEncMode_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void AdjustLocation();
        System::Void ActivateToolTip(bool Enable);
        System::Void SetStgEscKey(bool Enable);
        System::Boolean fcgLastX264ModeAsAMP;
        System::Void AdjustCXDropDownWidth(ComboBox^ CX);
        System::Void InitCXCmdExInsert();
        System::Void fcgCXCmdExInsert_FontChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgCXCmdExInsert_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgCXRC_SelectedIndexChanged(System::Object ^sender, System::EventArgs ^e);
        System::Void fcgNUQP_ValueChanged(System::Object^ sender, System::EventArgs^ e);
    public:
        System::Void InitData(CONF_GUIEX *set_config, const SYSTEM_DATA *system_data);
        System::Void SetVideoBitrate(int bitrate);
        System::Void SetAudioBitrate(int bitrate);
        System::Void InformfbcClosed();
    private:
        System::Boolean useAudioExt() {
            #if ENCODER_X264 || ENCODER_X265 || ENCODER_SVTAV1
                return true;
            #else
                return fcgCBAudioUseExt->Checked;
            #endif
        }
        System::Void fcgTSItem_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
            EnableSettingsNoteChange(false);
        }
    private:
        System::Void frmConfig_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
            if (e->KeyCode == Keys::Escape)
                this->Close();
            if ((e->KeyData & (Keys::Control | Keys::Shift | Keys::Enter)) == (Keys::Control | Keys::Shift | Keys::Enter))
                fcgBTOK_Click(sender, nullptr);
        }
    private:
        System::Void NUSelectAll(System::Object^  sender, System::EventArgs^  e) {
            NumericUpDown^ NU = dynamic_cast<NumericUpDown^>(sender);
            NU->Select(0, NU->Text->Length);
        }
    private:
        System::Void setComboBox(ComboBox^ CX, const ENC_OPTION_STR * list) {
            CX->BeginUpdate();
            const int prevIdx = CX->SelectedIndex;
            CX->Items->Clear();
            for (int i = 0; list[i].desc; i++) {
                String^ string = nullptr;
                if (list[i].mes != AUO_MES_UNKNOWN) {
                    string = LOAD_CLI_STRING(list[i].mes);
                } 
                if (string == nullptr || string->Length == 0) {
                    string = String(list[i].desc).ToString();
                }
                CX->Items->Add(string);
            }
            SetCXIndex(CX, prevIdx);
            CX->EndUpdate();
        }
    private:
        System::Void setComboBox(ComboBox ^CX, const CX_DESC_AUO *list) {
            CX->BeginUpdate();
            const int prevIdx = CX->SelectedIndex;
            CX->Items->Clear();
            for (int i = 0; list[i].desc; i++)
                CX->Items->Add(String(list[i].desc).ToString());
            SetCXIndex(CX, prevIdx);
            CX->EndUpdate();
        }
    private:
        System::Void setComboBox(ComboBox^ CX, const char * const * list) {
            CX->BeginUpdate();
            const int prevIdx = CX->SelectedIndex;
            CX->Items->Clear();
            for (int i = 0; list[i]; i++)
                CX->Items->Add(String(list[i]).ToString());
            SetCXIndex(CX, prevIdx);
            CX->EndUpdate();
        }
    private:
        System::Void setComboBox(ComboBox^ CX, const WCHAR * const * list) {
            CX->BeginUpdate();
            const int prevIdx = CX->SelectedIndex;
            CX->Items->Clear();
            for (int i = 0; list[i]; i++)
                CX->Items->Add(String(list[i]).ToString());
            SetCXIndex(CX, prevIdx);
            CX->EndUpdate();
        }
    private:
        System::Void setPriorityList(ComboBox^ CX) {
            CX->BeginUpdate();
            const int prevIdx = CX->SelectedIndex;
            CX->Items->Clear();
            for (int i = 0; priority_table[i].text; i++) {
                String^ string = nullptr;
                if (priority_table[i].mes != AUO_MES_UNKNOWN) {
                    string = LOAD_CLI_STRING(priority_table[i].mes);
                }
                if (string == nullptr || string->Length == 0) {
                    string = String(priority_table[i].text).ToString();
                }
                CX->Items->Add(string);
            }
            SetCXIndex(CX, prevIdx);
            CX->EndUpdate();
        }
    private:
        System::Void setMuxerCmdExNames(ComboBox^ CX, int muxer_index) {
            CX->BeginUpdate();
            const int prevIdx = CX->SelectedIndex;
            CX->Items->Clear();
            MUXER_SETTINGS *mstg = &sys_dat->exstg->s_mux[muxer_index];
            for (int i = 0; i < mstg->ex_count; i++)
                CX->Items->Add(String(mstg->ex_cmd[i].name).ToString());
            SetCXIndex(CX, prevIdx);
            CX->EndUpdate();
        }
    private:
        System::Void setAudioEncoderNames() {
            fcgCXAudioEncoder->BeginUpdate();
            const int prevIdx = fcgCXAudioEncoder->SelectedIndex;
            fcgCXAudioEncoder->Items->Clear();
            //fcgCXAudioEncoder->Items->AddRange(reinterpret_cast<array<String^>^>(LocalStg.audEncName->ToArray(String::typeid)));
            fcgCXAudioEncoder->Items->AddRange(LocalStg.audEncName->ToArray());
            SetCXIndex(fcgCXAudioEncoder, prevIdx);
            fcgCXAudioEncoder->EndUpdate();
        }
    private:
        System::Void TX_LimitbyBytes(System::Object^  sender, System::ComponentModel::CancelEventArgs^ e) {
            int maxLength = 0;
            int stringBytes = 0;
            TextBox^ TX = nullptr;
            if ((TX = dynamic_cast<TextBox^>(sender)) == nullptr)
                return;
            stringBytes = CountStringBytes(TX->Text);
            maxLength = TX->MaxLength;
            if (stringBytes > maxLength - 1) {
                e->Cancel = true;
                MessageBox::Show(this, LOAD_CLI_STRING(AUO_CONFIG_TEXT_LIMIT_LENGTH), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    private:
        System::Boolean openExeFile(TextBox^ TX, String^ ExeName) {
            //WinXPにおいて、OpenFileDialogはCurrentDirctoryを勝手に変更しやがるので、
            //一度保存し、あとから再適用する
            String^ CurrentDir = Directory::GetCurrentDirectory();
            OpenFileDialog ofd;
            ofd.Multiselect = false;
            ofd.FileName = ExeName;
            ofd.Filter = MakeExeFilter(ExeName);
            if (Directory::Exists(LocalStg.LastAppDir))
                ofd.InitialDirectory = Path::GetFullPath(LocalStg.LastAppDir);
            else if (File::Exists(TX->Text))
                ofd.InitialDirectory = Path::GetFullPath(Path::GetDirectoryName(TX->Text));
            else
                ofd.InitialDirectory = String(sys_dat->aviutl_dir).ToString();
            bool ret = (ofd.ShowDialog() == System::Windows::Forms::DialogResult::OK);
            if (ret) {
                if (sys_dat->exstg->s_local.get_relative_path)
                    ofd.FileName = GetRelativePath(ofd.FileName, CurrentDir);
                LocalStg.LastAppDir = Path::GetDirectoryName(Path::GetFullPath(ofd.FileName));
                TX->Text = ofd.FileName;
                TX->SelectionStart = TX->Text->Length;
            }
            Directory::SetCurrentDirectory(CurrentDir);
            return ret;
        }
    private:
        System::Void fcgBTX264Path_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openExeFile(fcgTXX264Path, LocalStg.x264ExeName))
                SetX264VersionToolTip(fcgTXX264Path->Text);
        }
    private:
        System::Void fcgBTX264PathSub_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openExeFile(fcgTXX264PathSub, LocalStg.x264ExeName))
                SetX264VersionToolTip(fcgTXX264PathSub->Text);
        }
    private:
        System::Void frmConfig::ExeTXPathEnter() {
            fcgTXX264Path_Enter(nullptr, nullptr);
            fcgTXX264PathSub_Enter(nullptr, nullptr);
            fcgTXAudioEncoderPath_Enter(nullptr, nullptr);
            fcgTXMP4MuxerPath_Enter(nullptr, nullptr);
            fcgTXTC2MP4Path_Enter(nullptr, nullptr);
            fcgTXMP4RawPath_Enter(nullptr, nullptr);
            fcgTXMKVMuxerPath_Enter(nullptr, nullptr);
        }
    private:
        System::Void frmConfig::ExeTXPathLeave() {
            fcgTXX264Path_Leave(nullptr, nullptr);
            fcgTXX264PathSub_Leave(nullptr, nullptr);
            fcgTXAudioEncoderPath_Leave(nullptr, nullptr);
            fcgTXMP4MuxerPath_Leave(nullptr, nullptr);
            fcgTXTC2MP4Path_Leave(nullptr, nullptr);
            fcgTXMP4RawPath_Leave(nullptr, nullptr);
            fcgTXMKVMuxerPath_Leave(nullptr, nullptr);
        }
    private:
        System::Void fcgTXX264Path_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXX264Path->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXX264Path->Text = L"";
            }
        }
    private:
        System::Void fcgTXX264Path_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXX264Path->Text->Length == 0) {
                fcgTXX264Path->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
            SetX264VersionToolTip(fcgTXX264Path->Text);
        }
    private:
        System::Void fcgTXX264PathSub_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXX264PathSub->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXX264PathSub->Text = L"";
            }
        }
    private:
        System::Void fcgTXX264PathSub_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXX264PathSub->Text->Length == 0) {
                fcgTXX264PathSub->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
            SetX264VersionToolTip(fcgTXX264PathSub->Text);
        }
    private:
        System::Void fcgTXAudioEncoderPath_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXAudioEncoderPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXAudioEncoderPath->Text = L"";
            }
        }
    private:
        System::Void fcgTXAudioEncoderPath_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXAudioEncoderPath->Text->Length == 0) {
                fcgTXAudioEncoderPath->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
        }
    private:
        System::Void fcgTXMP4MuxerPath_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMP4MuxerPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXMP4MuxerPath->Text = L"";
            }
        }
    private:
        System::Void fcgTXMP4MuxerPath_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMP4MuxerPath->Text->Length == 0) {
                fcgTXMP4MuxerPath->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
        }
    private:
        System::Void fcgTXTC2MP4Path_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXTC2MP4Path->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXTC2MP4Path->Text = L"";
            }
        }
    private:
        System::Void fcgTXTC2MP4Path_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXTC2MP4Path->Text->Length == 0) {
                fcgTXTC2MP4Path->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
        }
    private:
        System::Void fcgTXMP4RawPath_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMP4RawPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXMP4RawPath->Text = L"";
            }
        }
    private:
        System::Void fcgTXMP4RawPath_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMP4RawPath->Text->Length == 0) {
                fcgTXMP4RawPath->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
        }
    private:
        System::Void fcgTXMKVMuxerPath_Enter(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMKVMuxerPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXMKVMuxerPath->Text = L"";
            }
        }
    private:
        System::Void fcgTXMKVMuxerPath_Leave(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMKVMuxerPath->Text->Length == 0) {
                fcgTXMKVMuxerPath->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
            }
        }
    private:
        System::Void fcgBTMP4MuxerPath_Click(System::Object^  sender, System::EventArgs^  e) {
            openExeFile(fcgTXMP4MuxerPath, LocalStg.MP4MuxerExeName);
        }
    private:
        System::Void fcgBTTC2MP4Path_Click(System::Object^  sender, System::EventArgs^  e) {
            openExeFile(fcgTXTC2MP4Path, LocalStg.TC2MP4ExeName);
        }
    private:
        System::Void fcgBTMP4RawMuxerPath_Click(System::Object^  sender, System::EventArgs^  e) {
            openExeFile(fcgTXMP4RawPath, LocalStg.MP4RawExeName);
        }
    private:
        System::Void fcgBTAudioEncoderPath_Click(System::Object^  sender, System::EventArgs^  e) {
            int index = fcgCXAudioEncoder->SelectedIndex;
            openExeFile(fcgTXAudioEncoderPath, LocalStg.audEncExeName[index]);
        }
    private:
        System::Void fcgBTMKVMuxerPath_Click(System::Object^  sender, System::EventArgs^  e) {
            openExeFile(fcgTXMKVMuxerPath, LocalStg.MKVMuxerExeName);
        }
    private:
        System::Void openTempFolder(TextBox^ TX) {
            FolderBrowserDialog^ fbd = fcgfolderBrowserTemp;
            if (Directory::Exists(TX->Text))
                fbd->SelectedPath = TX->Text;
            if (fbd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                if (sys_dat->exstg->s_local.get_relative_path)
                    fbd->SelectedPath = GetRelativePath(fbd->SelectedPath);
                TX->Text = fbd->SelectedPath;
                TX->SelectionStart = TX->Text->Length;
            }
        }
    private:
        System::Void fcgBTCustomAudioTempDir_Click(System::Object^  sender, System::EventArgs^  e) {
            openTempFolder(fcgTXCustomAudioTempDir);
        }
    private:
        System::Void fcgBTMP4BoxTempDir_Click(System::Object^  sender, System::EventArgs^  e) {
            openTempFolder(fcgTXMP4BoxTempDir);
        }
    private:
        System::Void fcgBTCustomTempDir_Click(System::Object^  sender, System::EventArgs^  e) {
            openTempFolder(fcgTXCustomTempDir);
        }
    private:
        System::Boolean openAndSetFilePath(TextBox^ TX, String^ fileTypeName) {
            return openAndSetFilePath(TX, fileTypeName, nullptr, nullptr);
        }
    private:
        System::Boolean openAndSetFilePath(TextBox^ TX, String^ fileTypeName, String^ ext) {
            return openAndSetFilePath(TX, fileTypeName, ext, nullptr);
        }
    private:
        System::Boolean openAndSetFilePath(TextBox^ TX, String^ fileTypeName, String^ ext, String^ dir) {
            //WinXPにおいて、OpenFileDialogはCurrentDirctoryを勝手に変更しやがるので、
            //一度保存し、あとから再適用する
            String^ CurrentDir = Directory::GetCurrentDirectory();
            //設定
            if (ext == nullptr)
                ext = L".*";
            OpenFileDialog^ ofd = fcgOpenFileDialog;
            ofd->FileName = L"";
            if (dir != nullptr && Directory::Exists(dir))
                ofd->InitialDirectory = dir;
            if (TX->Text->Length) {
                String^ fileName = nullptr;
                try {
                    fileName = Path::GetFileName(TX->Text);
                } catch (...) {
                    //invalid charによる例外は破棄
                }
                if (fileName != nullptr)
                    ofd->FileName = fileName;
            }
            ofd->Multiselect = false;
            ofd->Filter = fileTypeName + L"(*" + ext + L")|*" + ext;
            bool ret = (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK);
            if (ret) {
                if (sys_dat->exstg->s_local.get_relative_path)
                    ofd->FileName = GetRelativePath(ofd->FileName, CurrentDir);
                TX->Text = ofd->FileName;
                TX->SelectionStart = TX->Text->Length;
            }
            Directory::SetCurrentDirectory(CurrentDir);
            return ret;
        }
    private:
        System::Void fcgBTStatusFile_Click(System::Object ^sender, System::EventArgs ^e) {
            openAndSetFilePath(fcgTXStatusFile, LOAD_CLI_STRING(AUO_CONFIG_STATUS_FILE));
        }
    private:
        System::Void fcgBTBatBeforePath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatBeforePath, LOAD_CLI_STRING(AUO_CONFIG_BAT_FILE), ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatBeforePath->Text);
        }
    private:
        System::Void fcgBTBatAfterPath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatAfterPath, LOAD_CLI_STRING(AUO_CONFIG_BAT_FILE), ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatAfterPath->Text);
        }
    private:
        System::Void fcgBTBatBeforeAudioPath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatBeforeAudioPath, LOAD_CLI_STRING(AUO_CONFIG_BAT_FILE), ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatBeforeAudioPath->Text);
        }
    private:
        System::Void fcgBTBatAfterAudioPath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatAfterAudioPath, LOAD_CLI_STRING(AUO_CONFIG_BAT_FILE), ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatAfterAudioPath->Text);
        }
    private:
        System::Void SetCXIndex(ComboBox^ CX, int index) {
            if (CX->Items->Count > 0) {
                CX->SelectedIndex = clamp(index, 0, CX->Items->Count - 1);
            }
        }
    private:
        System::Void SetNUValue(NumericUpDown^ NU, Decimal d) {
            NU->Value = clamp(d, NU->Minimum, NU->Maximum);
        }
    private:
        System::Void SetNUValue(NumericUpDown^ NU, int i) {
            NU->Value = clamp(Convert::ToDecimal(i), NU->Minimum, NU->Maximum);
        }
    private:
        System::Void SetNUValue(NumericUpDown^ NU, unsigned int i) {
            NU->Value = clamp(Convert::ToDecimal(i), NU->Minimum, NU->Maximum);
        }
    private:
        System::Void SetNUValue(NumericUpDown^ NU, float f) {
            NU->Value = clamp(Convert::ToDecimal(f), NU->Minimum, NU->Maximum);
        }
    private:
        System::Void SetNUValue(NumericUpDown^ NU, double d) {
            NU->Value = clamp(Convert::ToDecimal(d), NU->Minimum, NU->Maximum);
        }
    private:
        System::Int32 SetTBValue(TrackBar^ TB, int value) {
            int i = clamp(value, TB->Minimum, TB->Maximum);
            TB->Value = i;
            return i;
        }
    //private:
    //    System::Void fcgCBNulOut_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    //        if (fcgCBNulOut->Enabled)
    //            cnf_fcgTemp->nul_out = fcgCBNulOut->Checked;
    //    }
    //private:
    //    System::Void fcgCBSlowFirstPass_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
    //        if (fcgCBFastFirstPass->Enabled)
    //            cnf_fcgTemp->slow_first_pass = !fcgCBFastFirstPass->Checked;
    //    }
    private:
        System::Void fcgBTCmdEx_Click(System::Object^  sender, System::EventArgs^  e) {
            CONF_GUIEX cnf;
            init_CONF_GUIEX(&cnf, fcgCBUsehighbit->Checked);
            FrmToConf(&cnf);
            TCHAR cmdex[2048] = { 0 };
            GetWCHARfromString(cmdex, _countof(cmdex), fcgTXCmdEx->Text);
            CONF_ENC enc = get_default_prm();
            set_cmd(&enc, cnf.enc.cmd, true);
            set_cmd(&enc, cmdex, true);
            auto cmd_read = gen_cmd(&enc, false);
            _tcscpy_s(cnf.enc.cmd, cmd_read.c_str());
            ConfToFrm(&cnf, false);
        }
    private:
        System::Void frmConfig_Load(System::Object^  sender, System::EventArgs^  e) {
            InitForm();
        }
    private:
        System::Void frmConfig_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
#if ENABLE_AUOSETUP
            if (frmExeUpdate->waitingForUpdateFinishes())
                e->Cancel = true;
#endif
        }
    private:
        System::Void fcgBTOK_Click(System::Object^  sender, System::EventArgs^  e) {
            if (CheckLocalStg())
                return;
            init_CONF_GUIEX(conf, fcgCBUsehighbit->Checked);
            FrmToConf(conf);
            SaveLocalStg();
            ZeroMemory(conf->oth.notes, _countof(conf->oth.notes));
            this->Close();
        }
    private:
        System::Void fcgBTCancel_Click(System::Object^  sender, System::EventArgs^  e) {
            this->Close();
        }
    private:
        System::Void fcgBTDefault_Click(System::Object^  sender, System::EventArgs^  e) {
            CONF_GUIEX confDefault;
            init_CONF_GUIEX(&confDefault, FALSE);
            ConfToFrm(&confDefault, true);
        }
    private:
        System::Void ChangePresetNameDisplay(bool changed) {
            if (CheckedStgMenuItem != nullptr) {
                fcgTSSettings->Text = (changed) ? L"[" + CheckedStgMenuItem->Text + L"]*" : CheckedStgMenuItem->Text;
                fcgTSBSave->Enabled = changed;
            }
        }
    private:
        System::Void fcgRebuildCmd(System::Object^  sender, System::EventArgs^  e) {
            CONF_GUIEX rebuild;
            init_CONF_GUIEX(&rebuild, fcgCBUsehighbit->Checked);
            fcgTXCmd->Text = FrmToConf(&rebuild);
            if (CheckedStgMenuItem != nullptr)
                ChangePresetNameDisplay(memcmp(&rebuild, cnf_stgSelected, sizeof(CONF_GUIEX)) != 0);
        }
    private:
        System::Void CheckOtherChanges(System::Object^  sender, System::EventArgs^  e) {
            if (CheckedStgMenuItem == nullptr)
                return;
            CONF_GUIEX check_change;
            init_CONF_GUIEX(&check_change, fcgCBUsehighbit->Checked);
            FrmToConf(&check_change);
            ChangePresetNameDisplay(memcmp(&check_change, cnf_stgSelected, sizeof(CONF_GUIEX)) != 0);
        }
    private:
        System::Void fcgTXCmd_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
            int offset = (fcgTXCmd->Multiline) ? -fcgTXCmdfulloffset : fcgTXCmdfulloffset;
            fcgTXCmd->Height += offset;
            this->Height += offset;
            fcgTXCmd->Multiline = !fcgTXCmd->Multiline;
        }
    private:
        System::Void fcgTSSettings_Click(System::Object^  sender, System::EventArgs^  e) {
            if (EnableSettingsNoteChange(false))
                fcgTSSettings->ShowDropDown();
        }
    private:
        System::Void fcgBTTBQualityAdd_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
            timerChangeValue = 1;
            qualityTimer->Change(fcgTBQualityTimerLatency, fcgTBQualityTimerPeriod);
        }
    private:
        System::Void fcgBTTBQualityAdd_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
            qualityTimer->Change(System::Threading::Timeout::Infinite, fcgTBQualityTimerPeriod);
        }
    private:
        System::Void fcgBTTBQualitySubtract_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
            timerChangeValue = -1;
            qualityTimer->Change(fcgTBQualityTimerLatency, fcgTBQualityTimerPeriod);
        }
    private:
        System::Void fcgBTTBQualitySubtract_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
            qualityTimer->Change(System::Threading::Timeout::Infinite, fcgTBQualityTimerPeriod);
        }
    private:
        System::Void fcgTXX264Path_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXX264Path->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXX264PathSub->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
                LocalStg.x264Path = L"";
                fcgTXX264Path->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                int c = fcgTXX264Path->SelectionStart;
                LocalStg.x264Path = fcgTXX264Path->Text;
                fcgTXX264Path->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                fcgTXX264PathSub->Text = LocalStg.x264Path;
                fcgTXX264PathSub->SelectionStart = fcgTXX264PathSub->Text->Length;
                fcgTXX264Path->SelectionStart = c;
                fcgBTX264Path->ContextMenuStrip = (File::Exists(fcgTXX264Path->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXX264PathSub_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXX264PathSub->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                fcgTXX264Path->Text = LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH);
                LocalStg.x264Path = L"";
                fcgTXX264PathSub->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                LocalStg.x264Path = fcgTXX264PathSub->Text;
                fcgTXX264PathSub->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                int c = fcgTXX264PathSub->SelectionStart;
                fcgTXX264Path->Text = LocalStg.x264Path;
                fcgTXX264Path->SelectionStart = fcgTXX264Path->Text->Length;
                fcgTXX264PathSub->SelectionStart = c;
                fcgBTX264PathSub->ContextMenuStrip = (File::Exists(fcgTXX264PathSub->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXAudioEncoderPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgCXAudioEncoder->SelectedIndex < 0) return;
            if (fcgTXAudioEncoderPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex] = L"";
                fcgTXAudioEncoderPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                fcgTXAudioEncoderPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex] = fcgTXAudioEncoderPath->Text;
                fcgBTAudioEncoderPath->ContextMenuStrip = (File::Exists(fcgTXAudioEncoderPath->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXMP4MuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMP4MuxerPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                LocalStg.MP4MuxerPath = L"";
                fcgTXMP4MuxerPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                fcgTXMP4MuxerPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                LocalStg.MP4MuxerPath = fcgTXMP4MuxerPath->Text;
                fcgBTMP4MuxerPath->ContextMenuStrip = (File::Exists(fcgTXMP4MuxerPath->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXTC2MP4Path_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXTC2MP4Path->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                LocalStg.TC2MP4Path = L"";
                fcgTXTC2MP4Path->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                fcgTXTC2MP4Path->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                LocalStg.TC2MP4Path = fcgTXTC2MP4Path->Text;
                fcgBTTC2MP4Path->ContextMenuStrip = (File::Exists(fcgTXTC2MP4Path->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXMP4RawMuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMP4RawPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                LocalStg.MP4RawPath = L"";
                fcgTXMP4RawPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                fcgTXMP4RawPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                LocalStg.MP4RawPath = fcgTXMP4RawPath->Text;
                fcgBTMP4RawPath->ContextMenuStrip = (File::Exists(fcgTXMP4RawPath->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXMKVMuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            if (fcgTXMKVMuxerPath->Text == LOAD_CLI_STRING(AUO_CONFIG_CX_USE_DEFAULT_EXE_PATH)) {
                LocalStg.MKVMuxerPath = L"";
                fcgTXMKVMuxerPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Disabled);
            } else {
                fcgTXMKVMuxerPath->ForeColor = getTextBoxForeColor(themeMode, dwStgReader, DarkenWindowState::Normal);
                LocalStg.MKVMuxerPath = fcgTXMKVMuxerPath->Text;
                fcgBTMKVMuxerPath->ContextMenuStrip = (File::Exists(fcgTXMKVMuxerPath->Text)) ? fcgCSExeFiles : nullptr;
            }
        }
    private:
        System::Void fcgTXMP4BoxTempDir_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.CustomMP4TmpDir = fcgTXMP4BoxTempDir->Text;
        }
    private:
        System::Void fcgTXCustomAudioTempDir_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.CustomAudTmpDir = fcgTXCustomAudioTempDir->Text;
        }
    private:
        System::Void fcgTXCustomTempDir_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.CustomTmpDir = fcgTXCustomTempDir->Text;
        }
    private:
        System::Void fcgSetDragDropFilename_Enter(System::Object^  sender, DragEventArgs^  e) {
            e->Effect = (e->Data->GetDataPresent(DataFormats::FileDrop)) ? DragDropEffects::Copy : DragDropEffects::None;
        }
    private:
        System::Void fcgSetDragDropFilename_DragDrop(System::Object^  sender, DragEventArgs^  e) {
            TextBox^ TX = dynamic_cast<TextBox^>(sender);
            array<System::String ^>^ filelist = dynamic_cast<array<System::String ^>^>(e->Data->GetData(DataFormats::FileDrop, false));
            if (filelist == nullptr || TX == nullptr)
                return;
            String^ filePath = filelist[0]; //複数だった場合は先頭のものを使用
            if (sys_dat->exstg->s_local.get_relative_path)
                filePath = GetRelativePath(filePath);
            TX->Text = filePath;
        }
    private:
        System::Void fcgInsertDragDropFilename_Enter(System::Object^  sender, DragEventArgs^  e) {
            e->Effect = (   e->Data->GetDataPresent(DataFormats::FileDrop)
                         || e->Data->GetDataPresent(DataFormats::Text)
                         || e->Data->GetDataPresent(DataFormats::UnicodeText)
                         || e->Data->GetDataPresent(DataFormats::Rtf)
                         || e->Data->GetDataPresent(DataFormats::Html)) ? DragDropEffects::Copy : DragDropEffects::None;
        }
    private:
        System::Void fcgInsertDragDropFilename_DragOver(System::Object^  sender, DragEventArgs^  e) {
            TextBox^ TX = dynamic_cast<TextBox^>(sender);
            if (TX == nullptr)
                return;
            TX->Focus();
            this->Activate();
            //文字列がない部分の座標を指定した時に文字列の長さを返さない(一つ前の文字)になるため厄介
            //int index = TX->GetCharIndexFromPosition(TX->PointToClient(Point(e->X, e->Y)));
            //そこでEM_CHARFROMPOSメッセージを送る方法を使用する
            Point pint = TX->PointToClient(Point(e->X, e->Y));
            int p = ((pint.X & 0xffff) | (pint.Y << 16));
            int index = ::SendMessage((HWND)TX->Handle.ToPointer(), EM_CHARFROMPOS, 0, p) & 0xffff;
            TX->SelectionStart = index;
            //行・桁位置を求めるには以下の方法があるが、まあ今回は使わない
            //int line = TX->GetLineFromCharIndex(index);
            //int column = index - TX->GetFirstCharIndexFromLine(line);
        }
    private:
        System::Void fcgInsertDragDropFilename_DragDrop(System::Object^  sender, DragEventArgs^  e) {
            TextBox^ TX = dynamic_cast<TextBox^>(sender);
            if (TX == nullptr)
                return;
            String^ insertStr;
            if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
                array<System::String ^>^ filelist = dynamic_cast<array<System::String ^>^>(e->Data->GetData(DataFormats::FileDrop, false));
                if (filelist == nullptr)
                    return;
                for (int i = 0; i < filelist->Length; i++) {
                    if (i) insertStr += L" ";
                    insertStr += L"\"" + ((sys_dat->exstg->s_local.get_relative_path) ? GetRelativePath(filelist[i]) : filelist[i]) + L"\"";
                }
            } else {
                insertStr = dynamic_cast<System::String^>(e->Data->GetData(DataFormats::Text));
                if (insertStr == nullptr)
                    return;
            }
            int current_selection = TX->SelectionStart;
            TX->Text = TX->Text->Insert(TX->SelectionStart, insertStr);
            TX->SelectionStart = current_selection + insertStr->Length; //たまに変なところへ行くので念のため必要
        }
    private:
        System::Void fcgTSExeFileshelp_Click(System::Object^  sender, System::EventArgs^  e) {
            System::Windows::Forms::ToolStripMenuItem^ TS = dynamic_cast<System::Windows::Forms::ToolStripMenuItem^>(sender);
            if (TS == nullptr) return;
            System::Windows::Forms::ContextMenuStrip^ CS = dynamic_cast<System::Windows::Forms::ContextMenuStrip^>(TS->Owner);
            if (CS == nullptr) return;

            //Name, args, Path の順番
            array<ExeControls>^ ControlList = {
                { fcgBTX264Path->Name,           fcgTXX264Path->Text,           sys_dat->exstg->s_enc.help_cmd },
                { fcgBTX264PathSub->Name,        fcgTXX264PathSub->Text,        sys_dat->exstg->s_enc.help_cmd },
                { fcgBTAudioEncoderPath->Name,   fcgTXAudioEncoderPath->Text,   sys_dat->exstg->s_aud_ext[fcgCXAudioEncoder->SelectedIndex].cmd_help },
                { fcgBTMP4MuxerPath->Name,       fcgTXMP4MuxerPath->Text,       sys_dat->exstg->s_mux[MUXER_MP4].help_cmd },
                { fcgBTTC2MP4Path->Name,         fcgTXTC2MP4Path->Text,         sys_dat->exstg->s_mux[MUXER_TC2MP4].help_cmd },
                { fcgBTMP4RawPath->Name,         fcgTXMP4RawPath->Text,         sys_dat->exstg->s_mux[MUXER_MP4_RAW].help_cmd },
                { fcgBTMKVMuxerPath->Name,       fcgTXMKVMuxerPath->Text,       sys_dat->exstg->s_mux[MUXER_MKV].help_cmd },
            };
            for (int i = 0; i < ControlList->Length; i++) {
                if (NULL == String::Compare(CS->SourceControl->Name, ControlList[i].Name)) {
                    ShowExehelp(ControlList[i].Path, String(ControlList[i].args).ToString());
                    return;
                }
            }
            MessageBox::Show(LOAD_CLI_STRING(AUO_CONFIG_HELP_CMD_UNSET), LOAD_CLI_STRING(AUO_GUIEX_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    private:
        System::Void fcgLBguiExBlog_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
            fcgLBguiExBlog->LinkVisited = true;
            try {
                System::Diagnostics::Process::Start(String(sys_dat->exstg->blog_url).ToString());
            } catch (...) {
                //まあ放置
            };
        }
};
}
