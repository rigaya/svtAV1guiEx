﻿// -----------------------------------------------------------------------------------------
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

#pragma once

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
#if ENABLE_AUOSETUP
#include "frmUpdate.h"
#endif

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


namespace svtAV1guiEx {

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
            cnf_stgSelected = (CONF_GUIEX*)calloc(1, sizeof(CONF_GUIEX));
            InitializeComponent();
            //
            //TODO: ここにコンストラクタ コードを追加します
            //
            fcgLastX264ModeAsAMP = true;
        }

    protected:
        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        ~frmConfig()
        {
#if ENABLE_AUOSETUP
            if (nullptr != frmExeUpdate) {
                delete frmExeUpdate;
            }
#endif
            if (components)
            {
                delete components;
            }
            CloseBitrateCalc();
            if (cnf_stgSelected) free(cnf_stgSelected); cnf_stgSelected = NULL;
            if (qualityTimer != nullptr)
                delete qualityTimer;
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












private: System::Windows::Forms::TabPage^  fcgtabPageMPG;
private: System::Windows::Forms::Button^  fcgBTMPGMuxerPath;

private: System::Windows::Forms::TextBox^  fcgTXMPGMuxerPath;

private: System::Windows::Forms::Label^  fcgLBMPGMuxerPath;

private: System::Windows::Forms::ComboBox^  fcgCXMPGCmdEx;
private: System::Windows::Forms::Label^  fcgLBMPGMuxerCmdEx;
private: System::Windows::Forms::CheckBox^  fcgCBMPGMuxerExt;


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
private: System::Windows::Forms::ToolStripButton^  fcgTSBUpdate;

private: System::Windows::Forms::Label ^fcgLBThreads;
private: System::Windows::Forms::NumericUpDown ^fcgNUThreads;


private: System::Windows::Forms::Label ^fcgLBIntraRefreshType;
private: System::Windows::Forms::NumericUpDown ^fcgNUIntraRefreshType;
private: System::Windows::Forms::Label ^fcgLBKeyint;
private: System::Windows::Forms::NumericUpDown ^fcgNUKeyint;




private: System::Windows::Forms::Label ^fcgLBLookahead;
private: System::Windows::Forms::NumericUpDown ^fcgNULookaheadDistance;



























private: System::Windows::Forms::Label ^fcgLBSearch2;
private: System::Windows::Forms::Label ^fcgLBTile2;
private: System::Windows::Forms::NumericUpDown ^fcgNUSearchH;
private: System::Windows::Forms::Label ^fcgLBSearch;
private: System::Windows::Forms::NumericUpDown ^fcgNUSearchW;
private: System::Windows::Forms::NumericUpDown ^fcgNUTileColumns;
private: System::Windows::Forms::Label ^fcgLBTile;
private: System::Windows::Forms::NumericUpDown ^fcgNUTileRows;
private: System::Windows::Forms::Panel ^fcgPNX264Mode;
private: System::Windows::Forms::NumericUpDown ^fcgNUQP;
private: System::Windows::Forms::ComboBox ^fcgCXEncMode;
private: System::Windows::Forms::NumericUpDown ^fcgNUBitrate;
private: System::Windows::Forms::Label ^fcgLBHierarchicalLevels;

private: System::Windows::Forms::CheckBox ^fcgCBUseDefaultMeHme;
private: System::Windows::Forms::Label ^fcgLBAQ;
private: System::Windows::Forms::ComboBox ^fcgCXAQ;

private: System::Windows::Forms::Label ^fcgLBRC;
private: System::Windows::Forms::Label ^fcgLBEncMode;
private: System::Windows::Forms::Label ^fcgLBKbps;






private: System::Windows::Forms::ComboBox ^fcgCXEnableRedunduntBLK;


private: System::Windows::Forms::Label ^fcgLBEnableRedunduntBLK;


private: System::Windows::Forms::ComboBox ^fcgCXEnableMfmv;



private: System::Windows::Forms::Label ^fcgLBMfmv;












































private: System::Windows::Forms::Label ^fcgLBSQW;
private: System::Windows::Forms::NumericUpDown ^fcgNUSQW;





private: System::Windows::Forms::TabPage ^fcgtabPageSVTAV1_2;
private: System::Windows::Forms::Label ^fcgLBAltRefStrength;
private: System::Windows::Forms::NumericUpDown ^fcgNUAltRefStrength;
private: System::Windows::Forms::Label ^fcgLBAltRefNframes;
private: System::Windows::Forms::NumericUpDown ^fcgNUAltRefNframes;






private: System::Windows::Forms::ComboBox ^fcgCXEnableFilterIntra;
private: System::Windows::Forms::Label ^fcgLBEnableFilterIntra;
private: System::Windows::Forms::CheckBox ^fcgCBEnableGlobalMotion;
private: System::Windows::Forms::ComboBox ^fcgCXHighBitDepthModeDecision;
private: System::Windows::Forms::Label ^fcgLBHighBitDepthModeDecision;
private: System::Windows::Forms::ComboBox ^fcgCXIntraBCMode;
private: System::Windows::Forms::Label ^fcgLBIntraBCMode;
private: System::Windows::Forms::ComboBox ^fcgCXEnableIntraAngleDelta;
private: System::Windows::Forms::Label ^fcgLBEnableIntraAngleDelta;






private: System::Windows::Forms::ComboBox ^fcgCXEnablePaeth;
private: System::Windows::Forms::Label ^fcgLBEnablePaeth;


private: System::Windows::Forms::ComboBox ^fcgCXEnableSmooth;
private: System::Windows::Forms::Label ^fcgLBEnableSmooth;





























private: System::Windows::Forms::NumericUpDown ^fcgNUCDEFLevel;
private: System::Windows::Forms::Label ^fcgLBCDEFLevel;
private: System::Windows::Forms::ComboBox ^fcgCXWnFilterMode;
private: System::Windows::Forms::Label ^fcgLBWnFilterMode;
private: System::Windows::Forms::ComboBox ^fcgCXSgFilterMode;
private: System::Windows::Forms::Label ^fcgLBSgFilterMode;


private: System::Windows::Forms::Label ^fcgLBVBVBufSize;
private: System::Windows::Forms::NumericUpDown ^fcgNUVBVBufSize;
private: System::Windows::Forms::Label ^fcgLBMaxQP;
private: System::Windows::Forms::NumericUpDown ^fcgNUMaxQP;
private: System::Windows::Forms::Label ^fcgLBMinQP;
private: System::Windows::Forms::NumericUpDown ^fcgNUMinQP;
private: System::Windows::Forms::GroupBox ^fcggroupBoxColorMatrix;
private: System::Windows::Forms::ComboBox ^fcgCXInputRange;
private: System::Windows::Forms::Label ^fcgLBInputRange;
private: System::Windows::Forms::ComboBox ^fcgCXTransfer;
private: System::Windows::Forms::ComboBox ^fcgCXColorPrim;
private: System::Windows::Forms::ComboBox ^fcgCXColorMatrix;
private: System::Windows::Forms::Label ^fcgLBTransfer;
private: System::Windows::Forms::Label ^fcgLBColorPrim;
private: System::Windows::Forms::Label ^fcgLBColorMatrix;
private: System::Windows::Forms::GroupBox ^fcggroupBoxAepectRatio;
private: System::Windows::Forms::NumericUpDown ^fcgNUAspectRatioY;
private: System::Windows::Forms::Label ^fcgLBAspectRatio;
private: System::Windows::Forms::NumericUpDown ^fcgNUAspectRatioX;
private: System::Windows::Forms::ComboBox ^fcgCXAspectRatio;
private: System::Windows::Forms::ComboBox ^fcgCXEnableIntraEdgeSkp;
private: System::Windows::Forms::Label ^fcgLBEnableIntraEdgeSkp;
private: System::Windows::Forms::ComboBox ^fcgCXEnableIntraEdgeFilter;
private: System::Windows::Forms::Label ^fcgLBEnableIntraEdgeFilter;
private: System::Windows::Forms::ComboBox ^fcgCXEnableInterIntraComp;
private: System::Windows::Forms::Label ^fcgLBEnableInterIntraComp;


private: System::Windows::Forms::CheckBox ^fcgCBEnableStatReport;
private: System::Windows::Forms::ComboBox ^fcgCXDisableCfl;
private: System::Windows::Forms::Label ^fcgLBDisableCfl;


private: System::Windows::Forms::ComboBox ^fcgCXChromaMode;
private: System::Windows::Forms::Label ^fcgLBChromaMode;




private: System::Windows::Forms::ComboBox ^fcgCXEnableFrameEndCdfUpdate;
private: System::Windows::Forms::Label ^fcgLBEnableFrameEndCdfUpdate;
private: System::Windows::Forms::ComboBox ^fcgCXEnableOverBoundryBlock;
private: System::Windows::Forms::Label ^fcgLBEnableOverBoundryBlock;
private: System::Windows::Forms::ComboBox ^fcgCXEnableNewNearestCombInjection;
private: System::Windows::Forms::Label ^fcgLBEnableNewNearestCombInjection;
private: System::Windows::Forms::ComboBox ^fcgCXSubpel;
private: System::Windows::Forms::Label ^fcgLBSubpel;
private: System::Windows::Forms::ComboBox ^fcgCXEnableRestortionFiltering;
private: System::Windows::Forms::Label ^fcgLBEnableRestortionFiltering;
private: System::Windows::Forms::ComboBox ^fcgCXEnableSpatialSSEfl;
private: System::Windows::Forms::Label ^fcgLBEnableSpatialSSEfl;


private: System::Windows::Forms::ComboBox ^fcgCXUMV;
private: System::Windows::Forms::Label ^fcgLBUMV;
private: System::Windows::Forms::ComboBox ^fcgCXPalette;
private: System::Windows::Forms::Label ^fcgLBPalette;
private: System::Windows::Forms::ComboBox ^fcgCXPredMe;
private: System::Windows::Forms::Label ^fcgLBPredMe;
private: System::Windows::Forms::ComboBox ^fcgCXSCM;
private: System::Windows::Forms::Label ^fcgLBScm;
private: System::Windows::Forms::ComboBox ^fcgCXCompund;
private: System::Windows::Forms::Label ^fcgLBCompund;
private: System::Windows::Forms::ComboBox ^fcgCXRDOQ;
private: System::Windows::Forms::Label ^fcgLBRDOQ;
private: System::Windows::Forms::ComboBox ^fcgCXBipred3x3;
private: System::Windows::Forms::Label ^fcgLBBipred3x3;

private: System::Windows::Forms::Label ^fcgLBTFLevel;
private: System::Windows::Forms::ComboBox ^fcgCXExtBlock;
private: System::Windows::Forms::Label ^fcgLBExtBlock;
private: System::Windows::Forms::Label ^fcgLB2pasAuto;
private: System::Windows::Forms::CheckBox ^fcgCB2PassAuto;
private: System::Windows::Forms::ComboBox ^fcgCXProfileAV1;
private: System::Windows::Forms::Label ^fcgLBProfileAV1;


private: System::Windows::Forms::ComboBox ^fcgCXColorFormat;

private: System::Windows::Forms::Label ^fcgLBColorFormat;
private: System::Windows::Forms::ComboBox ^fcgCXMrpLevel;
private: System::Windows::Forms::Label ^fcgLBMrpLevel;
private: System::Windows::Forms::ComboBox ^fcgCXObmcLevel;
private: System::Windows::Forms::Label ^fcgLBObmcLevel;
private: System::Windows::Forms::Label ^fcgLBOverShootPct;
private: System::Windows::Forms::NumericUpDown ^fcgNUOverShootPct;
private: System::Windows::Forms::Label ^fcgLBUnderShootPct;
private: System::Windows::Forms::NumericUpDown ^fcgNUUnderShootPct;
private: System::Windows::Forms::Label ^fcgLBMaxSectionPct;
private: System::Windows::Forms::NumericUpDown ^fcgNUMaxSectionPct;
private: System::Windows::Forms::Label ^fcgLBMinSectionPct;
private: System::Windows::Forms::NumericUpDown ^fcgNUMinSectionPct;
private: System::Windows::Forms::Label ^fcgLBBiasPct;
private: System::Windows::Forms::NumericUpDown ^fcgNUBiasPct;
private: System::Windows::Forms::Label ^fcgLBSTATUS;
private: System::Windows::Forms::TextBox ^fcgTXStatusFile;
private: System::Windows::Forms::Button ^fcgBTStatusFile;
private: System::Windows::Forms::CheckBox ^fcgCBAfs24fpsMode;
private: System::Windows::Forms::ComboBox ^fcgCXTFLevel;
private: System::Windows::Forms::ComboBox ^fcgCXHierarchicalLevels;
private: System::Windows::Forms::Label ^fcgLBEnableStatReport;
private: System::Windows::Forms::Label ^fcgLBEnableGlobalMotion;
private: System::Windows::Forms::Label ^fcgLBUseDefaultMeHme;
private: System::Windows::Forms::ComboBox ^fcgCXEnableLocalWarp;
private: System::Windows::Forms::Label ^fcgLBEnableLocalWarp;

































































































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
            System::ComponentModel::ComponentResourceManager ^resources = (gcnew System::ComponentModel::ComponentResourceManager(frmConfig::typeid));
            this->fcgtabControlVideo = (gcnew System::Windows::Forms::TabControl());
            this->fcgtabPageSVTAV1_1 = (gcnew System::Windows::Forms::TabPage());
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
            this->fcgCBEnableStatReport = (gcnew System::Windows::Forms::CheckBox());
            this->fcgCXDisableCfl = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBDisableCfl = (gcnew System::Windows::Forms::Label());
            this->fcgCXChromaMode = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBChromaMode = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableFrameEndCdfUpdate = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableFrameEndCdfUpdate = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableOverBoundryBlock = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableOverBoundryBlock = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableNewNearestCombInjection = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableNewNearestCombInjection = (gcnew System::Windows::Forms::Label());
            this->fcgCXSubpel = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBSubpel = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableRestortionFiltering = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableRestortionFiltering = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableSpatialSSEfl = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableSpatialSSEfl = (gcnew System::Windows::Forms::Label());
            this->fcgNUCDEFLevel = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBCDEFLevel = (gcnew System::Windows::Forms::Label());
            this->fcgCXWnFilterMode = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBWnFilterMode = (gcnew System::Windows::Forms::Label());
            this->fcgCXSgFilterMode = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBSgFilterMode = (gcnew System::Windows::Forms::Label());
            this->fcgLBVBVBufSize = (gcnew System::Windows::Forms::Label());
            this->fcgNUVBVBufSize = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMaxQP = (gcnew System::Windows::Forms::Label());
            this->fcgNUMaxQP = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMinQP = (gcnew System::Windows::Forms::Label());
            this->fcgNUMinQP = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCBEnableGlobalMotion = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBSQW = (gcnew System::Windows::Forms::Label());
            this->fcgNUSQW = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXEnableRedunduntBLK = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableRedunduntBLK = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableMfmv = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMfmv = (gcnew System::Windows::Forms::Label());
            this->fcgLBAQ = (gcnew System::Windows::Forms::Label());
            this->fcgCXAQ = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCBUseDefaultMeHme = (gcnew System::Windows::Forms::CheckBox());
            this->fcgLBHierarchicalLevels = (gcnew System::Windows::Forms::Label());
            this->fcgLBSearch2 = (gcnew System::Windows::Forms::Label());
            this->fcgLBTile2 = (gcnew System::Windows::Forms::Label());
            this->fcgNUSearchH = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBSearch = (gcnew System::Windows::Forms::Label());
            this->fcgNUSearchW = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgNUTileColumns = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBTile = (gcnew System::Windows::Forms::Label());
            this->fcgNUTileRows = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBIntraRefreshType = (gcnew System::Windows::Forms::Label());
            this->fcgNUIntraRefreshType = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBKeyint = (gcnew System::Windows::Forms::Label());
            this->fcgNUKeyint = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBLookahead = (gcnew System::Windows::Forms::Label());
            this->fcgNULookaheadDistance = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBThreads = (gcnew System::Windows::Forms::Label());
            this->fcgNUThreads = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCBUsehighbit = (gcnew System::Windows::Forms::CheckBox());
            this->fcgBTX264Path = (gcnew System::Windows::Forms::Button());
            this->fcgTXX264Path = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBX264Path = (gcnew System::Windows::Forms::Label());
            this->fcgtabPageSVTAV1_2 = (gcnew System::Windows::Forms::TabPage());
            this->fcgCXTFLevel = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBSTATUS = (gcnew System::Windows::Forms::Label());
            this->fcgTXStatusFile = (gcnew System::Windows::Forms::TextBox());
            this->fcgBTStatusFile = (gcnew System::Windows::Forms::Button());
            this->fcgLBBiasPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUBiasPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBOverShootPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUOverShootPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBUnderShootPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUUnderShootPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMaxSectionPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUMaxSectionPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBMinSectionPct = (gcnew System::Windows::Forms::Label());
            this->fcgNUMinSectionPct = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXMrpLevel = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMrpLevel = (gcnew System::Windows::Forms::Label());
            this->fcgCXObmcLevel = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBObmcLevel = (gcnew System::Windows::Forms::Label());
            this->fcgCXExtBlock = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBExtBlock = (gcnew System::Windows::Forms::Label());
            this->fcgLBTFLevel = (gcnew System::Windows::Forms::Label());
            this->fcgCXUMV = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBUMV = (gcnew System::Windows::Forms::Label());
            this->fcgCXPalette = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBPalette = (gcnew System::Windows::Forms::Label());
            this->fcgCXPredMe = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBPredMe = (gcnew System::Windows::Forms::Label());
            this->fcgCXSCM = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBScm = (gcnew System::Windows::Forms::Label());
            this->fcgCXCompund = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBCompund = (gcnew System::Windows::Forms::Label());
            this->fcgCXRDOQ = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBRDOQ = (gcnew System::Windows::Forms::Label());
            this->fcgCXBipred3x3 = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBBipred3x3 = (gcnew System::Windows::Forms::Label());
            this->fcggroupBoxColorMatrix = (gcnew System::Windows::Forms::GroupBox());
            this->fcgCXInputRange = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBInputRange = (gcnew System::Windows::Forms::Label());
            this->fcgCXTransfer = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXColorPrim = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXColorMatrix = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBTransfer = (gcnew System::Windows::Forms::Label());
            this->fcgLBColorPrim = (gcnew System::Windows::Forms::Label());
            this->fcgLBColorMatrix = (gcnew System::Windows::Forms::Label());
            this->fcggroupBoxAepectRatio = (gcnew System::Windows::Forms::GroupBox());
            this->fcgNUAspectRatioY = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBAspectRatio = (gcnew System::Windows::Forms::Label());
            this->fcgNUAspectRatioX = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgCXAspectRatio = (gcnew System::Windows::Forms::ComboBox());
            this->fcgCXEnableIntraEdgeSkp = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableIntraEdgeSkp = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableIntraEdgeFilter = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableIntraEdgeFilter = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableInterIntraComp = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableInterIntraComp = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnablePaeth = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnablePaeth = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableSmooth = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableSmooth = (gcnew System::Windows::Forms::Label());
            this->fcgCXIntraBCMode = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBIntraBCMode = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableIntraAngleDelta = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableIntraAngleDelta = (gcnew System::Windows::Forms::Label());
            this->fcgCXHighBitDepthModeDecision = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBHighBitDepthModeDecision = (gcnew System::Windows::Forms::Label());
            this->fcgCXEnableFilterIntra = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableFilterIntra = (gcnew System::Windows::Forms::Label());
            this->fcgLBAltRefNframes = (gcnew System::Windows::Forms::Label());
            this->fcgNUAltRefNframes = (gcnew System::Windows::Forms::NumericUpDown());
            this->fcgLBAltRefStrength = (gcnew System::Windows::Forms::Label());
            this->fcgNUAltRefStrength = (gcnew System::Windows::Forms::NumericUpDown());
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
            this->fcgCBAfs24fpsMode = (gcnew System::Windows::Forms::CheckBox());
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
            this->fcgTSBBitrateCalc = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
            this->fcgTSBUpdate = (gcnew System::Windows::Forms::ToolStripButton());
            this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
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
            this->fcgtabPageMPG = (gcnew System::Windows::Forms::TabPage());
            this->fcgBTMPGMuxerPath = (gcnew System::Windows::Forms::Button());
            this->fcgTXMPGMuxerPath = (gcnew System::Windows::Forms::TextBox());
            this->fcgLBMPGMuxerPath = (gcnew System::Windows::Forms::Label());
            this->fcgCXMPGCmdEx = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBMPGMuxerCmdEx = (gcnew System::Windows::Forms::Label());
            this->fcgCBMPGMuxerExt = (gcnew System::Windows::Forms::CheckBox());
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
            this->fcgCXEnableLocalWarp = (gcnew System::Windows::Forms::ComboBox());
            this->fcgLBEnableLocalWarp = (gcnew System::Windows::Forms::Label());
            this->fcgLBUseDefaultMeHme = (gcnew System::Windows::Forms::Label());
            this->fcgLBEnableGlobalMotion = (gcnew System::Windows::Forms::Label());
            this->fcgLBEnableStatReport = (gcnew System::Windows::Forms::Label());
            this->fcgtabControlVideo->SuspendLayout();
            this->fcgtabPageSVTAV1_1->SuspendLayout();
            this->fcgPNX264Mode->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUBitrate))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUQP))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUCDEFLevel))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUVBVBufSize))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMaxQP))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMinQP))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUSQW))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUSearchH))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUSearchW))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUTileColumns))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUTileRows))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUIntraRefreshType))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUKeyint))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNULookaheadDistance))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUThreads))->BeginInit();
            this->fcgtabPageSVTAV1_2->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUBiasPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUOverShootPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUUnderShootPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMaxSectionPct))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMinSectionPct))->BeginInit();
            this->fcggroupBoxColorMatrix->SuspendLayout();
            this->fcggroupBoxAepectRatio->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAspectRatioY))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAspectRatioX))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAltRefNframes))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAltRefStrength))->BeginInit();
            this->fcgtabPageExSettings->SuspendLayout();
            this->fcggroupBoxCmdEx->SuspendLayout();
            this->fcggroupBoxExSettings->SuspendLayout();
            this->fcgCSExeFiles->SuspendLayout();
            this->fcgtoolStripSettings->SuspendLayout();
            this->fcgtabControlMux->SuspendLayout();
            this->fcgtabPageMP4->SuspendLayout();
            this->fcgtabPageMKV->SuspendLayout();
            this->fcgtabPageMPG->SuspendLayout();
            this->fcgtabPageMux->SuspendLayout();
            this->fcgtabPageBat->SuspendLayout();
            this->fcgtabControlAudio->SuspendLayout();
            this->fcgtabPageAudioMain->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAudioBitrate))->BeginInit();
            this->fcgtabPageAudioOther->SuspendLayout();
            this->SuspendLayout();
            // 
            // fcgtabControlVideo
            // 
            this->fcgtabControlVideo->Controls->Add(this->fcgtabPageSVTAV1_1);
            this->fcgtabControlVideo->Controls->Add(this->fcgtabPageSVTAV1_2);
            this->fcgtabControlVideo->Controls->Add(this->fcgtabPageExSettings);
            this->fcgtabControlVideo->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgtabControlVideo->Location = System::Drawing::Point(0, 25);
            this->fcgtabControlVideo->Name = L"fcgtabControlVideo";
            this->fcgtabControlVideo->SelectedIndex = 0;
            this->fcgtabControlVideo->Size = System::Drawing::Size(616, 520);
            this->fcgtabControlVideo->TabIndex = 0;
            // 
            // fcgtabPageSVTAV1_1
            // 
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableStatReport);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableGlobalMotion);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBUseDefaultMeHme);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableLocalWarp);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableLocalWarp);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXHierarchicalLevels);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgPNX264Mode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLB2pasAuto);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCB2PassAuto);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXProfileAV1);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBProfileAV1);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXColorFormat);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBColorFormat);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBEnableStatReport);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXDisableCfl);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBDisableCfl);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXChromaMode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBChromaMode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableFrameEndCdfUpdate);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableFrameEndCdfUpdate);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableOverBoundryBlock);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableOverBoundryBlock);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableNewNearestCombInjection);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableNewNearestCombInjection);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXSubpel);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSubpel);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableRestortionFiltering);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableRestortionFiltering);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableSpatialSSEfl);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableSpatialSSEfl);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUCDEFLevel);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBCDEFLevel);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXWnFilterMode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBWnFilterMode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXSgFilterMode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSgFilterMode);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBVBVBufSize);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUVBVBufSize);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMaxQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUMaxQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMinQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUMinQP);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBEnableGlobalMotion);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSQW);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUSQW);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableRedunduntBLK);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBEnableRedunduntBLK);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXEnableMfmv);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBMfmv);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBAQ);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCXAQ);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBUseDefaultMeHme);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBHierarchicalLevels);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSearch2);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBTile2);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUSearchH);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBSearch);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUSearchW);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUTileColumns);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBTile);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUTileRows);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBIntraRefreshType);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUIntraRefreshType);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBKeyint);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUKeyint);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBLookahead);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNULookaheadDistance);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBThreads);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgNUThreads);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgCBUsehighbit);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgBTX264Path);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgTXX264Path);
            this->fcgtabPageSVTAV1_1->Controls->Add(this->fcgLBX264Path);
            this->fcgtabPageSVTAV1_1->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageSVTAV1_1->Name = L"fcgtabPageSVTAV1_1";
            this->fcgtabPageSVTAV1_1->Padding = System::Windows::Forms::Padding(3);
            this->fcgtabPageSVTAV1_1->Size = System::Drawing::Size(608, 493);
            this->fcgtabPageSVTAV1_1->TabIndex = 0;
            this->fcgtabPageSVTAV1_1->Text = L"SVT-AV1 (1)";
            this->fcgtabPageSVTAV1_1->UseVisualStyleBackColor = true;
            // 
            // fcgCXHierarchicalLevels
            // 
            this->fcgCXHierarchicalLevels->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXHierarchicalLevels->FormattingEnabled = true;
            this->fcgCXHierarchicalLevels->Location = System::Drawing::Point(482, 225);
            this->fcgCXHierarchicalLevels->Name = L"fcgCXHierarchicalLevels";
            this->fcgCXHierarchicalLevels->Size = System::Drawing::Size(118, 22);
            this->fcgCXHierarchicalLevels->TabIndex = 227;
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
            this->fcgLBKbps->Location = System::Drawing::Point(339, 10);
            this->fcgLBKbps->Name = L"fcgLBKbps";
            this->fcgLBKbps->Size = System::Drawing::Size(32, 14);
            this->fcgLBKbps->TabIndex = 76;
            this->fcgLBKbps->Text = L"kbps";
            // 
            // fcgLBRC
            // 
            this->fcgLBRC->AutoSize = true;
            this->fcgLBRC->Location = System::Drawing::Point(9, 10);
            this->fcgLBRC->Name = L"fcgLBRC";
            this->fcgLBRC->Size = System::Drawing::Size(54, 14);
            this->fcgLBRC->TabIndex = 75;
            this->fcgLBRC->Text = L"レート制御";
            // 
            // fcgLBEncMode
            // 
            this->fcgLBEncMode->AutoSize = true;
            this->fcgLBEncMode->Location = System::Drawing::Point(9, 44);
            this->fcgLBEncMode->Name = L"fcgLBEncMode";
            this->fcgLBEncMode->Size = System::Drawing::Size(51, 14);
            this->fcgLBEncMode->TabIndex = 74;
            this->fcgLBEncMode->Text = L"速度設定";
            // 
            // fcgNUBitrate
            // 
            this->fcgNUBitrate->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
            this->fcgNUBitrate->Location = System::Drawing::Point(254, 8);
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
            this->fcgCXEncMode->Location = System::Drawing::Point(84, 41);
            this->fcgCXEncMode->Name = L"fcgCXEncMode";
            this->fcgCXEncMode->Size = System::Drawing::Size(164, 22);
            this->fcgCXEncMode->TabIndex = 7;
            this->fcgCXEncMode->Tag = L"reCmd";
            // 
            // fcgNUQP
            // 
            this->fcgNUQP->Location = System::Drawing::Point(262, 8);
            this->fcgNUQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
            this->fcgNUQP->Name = L"fcgNUQP";
            this->fcgNUQP->Size = System::Drawing::Size(64, 21);
            this->fcgNUQP->TabIndex = 65;
            this->fcgNUQP->Tag = L"reCmd";
            this->fcgNUQP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCXRC
            // 
            this->fcgCXRC->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXRC->FormattingEnabled = true;
            this->fcgCXRC->Location = System::Drawing::Point(84, 7);
            this->fcgCXRC->Name = L"fcgCXRC";
            this->fcgCXRC->Size = System::Drawing::Size(164, 22);
            this->fcgCXRC->TabIndex = 5;
            this->fcgCXRC->Tag = L"reCmd";
            this->fcgCXRC->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfig::fcgCXRC_SelectedIndexChanged);
            // 
            // fcgLB2pasAuto
            // 
            this->fcgLB2pasAuto->AutoSize = true;
            this->fcgLB2pasAuto->Location = System::Drawing::Point(417, 14);
            this->fcgLB2pasAuto->Name = L"fcgLB2pasAuto";
            this->fcgLB2pasAuto->Size = System::Drawing::Size(70, 14);
            this->fcgLB2pasAuto->TabIndex = 226;
            this->fcgLB2pasAuto->Text = L"2pass Mode";
            // 
            // fcgCB2PassAuto
            // 
            this->fcgCB2PassAuto->AutoSize = true;
            this->fcgCB2PassAuto->Location = System::Drawing::Point(527, 15);
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
            this->fcgCXProfileAV1->Location = System::Drawing::Point(482, 171);
            this->fcgCXProfileAV1->Name = L"fcgCXProfileAV1";
            this->fcgCXProfileAV1->Size = System::Drawing::Size(118, 22);
            this->fcgCXProfileAV1->TabIndex = 60;
            this->fcgCXProfileAV1->Tag = L"reCmd";
            // 
            // fcgLBProfileAV1
            // 
            this->fcgLBProfileAV1->AutoSize = true;
            this->fcgLBProfileAV1->Location = System::Drawing::Point(375, 174);
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
            this->fcgCXColorFormat->Location = System::Drawing::Point(482, 198);
            this->fcgCXColorFormat->Name = L"fcgCXColorFormat";
            this->fcgCXColorFormat->Size = System::Drawing::Size(118, 22);
            this->fcgCXColorFormat->TabIndex = 61;
            this->fcgCXColorFormat->Tag = L"reCmd";
            // 
            // fcgLBColorFormat
            // 
            this->fcgLBColorFormat->AutoSize = true;
            this->fcgLBColorFormat->Location = System::Drawing::Point(374, 201);
            this->fcgLBColorFormat->Name = L"fcgLBColorFormat";
            this->fcgLBColorFormat->Size = System::Drawing::Size(79, 14);
            this->fcgLBColorFormat->TabIndex = 220;
            this->fcgLBColorFormat->Text = L"Color Format";
            // 
            // fcgCBEnableStatReport
            // 
            this->fcgCBEnableStatReport->AutoSize = true;
            this->fcgCBEnableStatReport->Location = System::Drawing::Point(517, 470);
            this->fcgCBEnableStatReport->Name = L"fcgCBEnableStatReport";
            this->fcgCBEnableStatReport->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableStatReport->TabIndex = 97;
            this->fcgCBEnableStatReport->Tag = L"reCmd";
            this->fcgCBEnableStatReport->UseVisualStyleBackColor = true;
            // 
            // fcgCXDisableCfl
            // 
            this->fcgCXDisableCfl->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXDisableCfl->FormattingEnabled = true;
            this->fcgCXDisableCfl->Location = System::Drawing::Point(165, 455);
            this->fcgCXDisableCfl->Name = L"fcgCXDisableCfl";
            this->fcgCXDisableCfl->Size = System::Drawing::Size(118, 22);
            this->fcgCXDisableCfl->TabIndex = 32;
            this->fcgCXDisableCfl->Tag = L"reCmd";
            // 
            // fcgLBDisableCfl
            // 
            this->fcgLBDisableCfl->AutoSize = true;
            this->fcgLBDisableCfl->Location = System::Drawing::Point(15, 458);
            this->fcgLBDisableCfl->Name = L"fcgLBDisableCfl";
            this->fcgLBDisableCfl->Size = System::Drawing::Size(59, 14);
            this->fcgLBDisableCfl->TabIndex = 213;
            this->fcgLBDisableCfl->Text = L"DisableCfl";
            // 
            // fcgCXChromaMode
            // 
            this->fcgCXChromaMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXChromaMode->FormattingEnabled = true;
            this->fcgCXChromaMode->Location = System::Drawing::Point(165, 429);
            this->fcgCXChromaMode->Name = L"fcgCXChromaMode";
            this->fcgCXChromaMode->Size = System::Drawing::Size(118, 22);
            this->fcgCXChromaMode->TabIndex = 31;
            this->fcgCXChromaMode->Tag = L"reCmd";
            // 
            // fcgLBChromaMode
            // 
            this->fcgLBChromaMode->AutoSize = true;
            this->fcgLBChromaMode->Location = System::Drawing::Point(15, 432);
            this->fcgLBChromaMode->Name = L"fcgLBChromaMode";
            this->fcgLBChromaMode->Size = System::Drawing::Size(79, 14);
            this->fcgLBChromaMode->TabIndex = 209;
            this->fcgLBChromaMode->Text = L"ChromaMode";
            // 
            // fcgCXEnableFrameEndCdfUpdate
            // 
            this->fcgCXEnableFrameEndCdfUpdate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableFrameEndCdfUpdate->FormattingEnabled = true;
            this->fcgCXEnableFrameEndCdfUpdate->Location = System::Drawing::Point(165, 403);
            this->fcgCXEnableFrameEndCdfUpdate->Name = L"fcgCXEnableFrameEndCdfUpdate";
            this->fcgCXEnableFrameEndCdfUpdate->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableFrameEndCdfUpdate->TabIndex = 30;
            this->fcgCXEnableFrameEndCdfUpdate->Tag = L"reCmd";
            // 
            // fcgLBEnableFrameEndCdfUpdate
            // 
            this->fcgLBEnableFrameEndCdfUpdate->AutoSize = true;
            this->fcgLBEnableFrameEndCdfUpdate->Location = System::Drawing::Point(15, 406);
            this->fcgLBEnableFrameEndCdfUpdate->Name = L"fcgLBEnableFrameEndCdfUpdate";
            this->fcgLBEnableFrameEndCdfUpdate->Size = System::Drawing::Size(118, 14);
            this->fcgLBEnableFrameEndCdfUpdate->TabIndex = 201;
            this->fcgLBEnableFrameEndCdfUpdate->Text = L"FrameEndCdfUpdate";
            // 
            // fcgCXEnableOverBoundryBlock
            // 
            this->fcgCXEnableOverBoundryBlock->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableOverBoundryBlock->FormattingEnabled = true;
            this->fcgCXEnableOverBoundryBlock->Location = System::Drawing::Point(165, 351);
            this->fcgCXEnableOverBoundryBlock->Name = L"fcgCXEnableOverBoundryBlock";
            this->fcgCXEnableOverBoundryBlock->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableOverBoundryBlock->TabIndex = 28;
            this->fcgCXEnableOverBoundryBlock->Tag = L"reCmd";
            // 
            // fcgLBEnableOverBoundryBlock
            // 
            this->fcgLBEnableOverBoundryBlock->AutoSize = true;
            this->fcgLBEnableOverBoundryBlock->Location = System::Drawing::Point(15, 354);
            this->fcgLBEnableOverBoundryBlock->Name = L"fcgLBEnableOverBoundryBlock";
            this->fcgLBEnableOverBoundryBlock->Size = System::Drawing::Size(107, 14);
            this->fcgLBEnableOverBoundryBlock->TabIndex = 199;
            this->fcgLBEnableOverBoundryBlock->Text = L"OverBoundryBlock";
            // 
            // fcgCXEnableNewNearestCombInjection
            // 
            this->fcgCXEnableNewNearestCombInjection->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableNewNearestCombInjection->FormattingEnabled = true;
            this->fcgCXEnableNewNearestCombInjection->Location = System::Drawing::Point(165, 377);
            this->fcgCXEnableNewNearestCombInjection->Name = L"fcgCXEnableNewNearestCombInjection";
            this->fcgCXEnableNewNearestCombInjection->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableNewNearestCombInjection->TabIndex = 29;
            this->fcgCXEnableNewNearestCombInjection->Tag = L"reCmd";
            // 
            // fcgLBEnableNewNearestCombInjection
            // 
            this->fcgLBEnableNewNearestCombInjection->AutoSize = true;
            this->fcgLBEnableNewNearestCombInjection->Location = System::Drawing::Point(15, 380);
            this->fcgLBEnableNewNearestCombInjection->Name = L"fcgLBEnableNewNearestCombInjection";
            this->fcgLBEnableNewNearestCombInjection->Size = System::Drawing::Size(150, 14);
            this->fcgLBEnableNewNearestCombInjection->TabIndex = 197;
            this->fcgLBEnableNewNearestCombInjection->Text = L"NewNearestCombInjection";
            // 
            // fcgCXSubpel
            // 
            this->fcgCXSubpel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXSubpel->FormattingEnabled = true;
            this->fcgCXSubpel->Location = System::Drawing::Point(165, 325);
            this->fcgCXSubpel->Name = L"fcgCXSubpel";
            this->fcgCXSubpel->Size = System::Drawing::Size(118, 22);
            this->fcgCXSubpel->TabIndex = 27;
            this->fcgCXSubpel->Tag = L"reCmd";
            // 
            // fcgLBSubpel
            // 
            this->fcgLBSubpel->AutoSize = true;
            this->fcgLBSubpel->Location = System::Drawing::Point(15, 328);
            this->fcgLBSubpel->Name = L"fcgLBSubpel";
            this->fcgLBSubpel->Size = System::Drawing::Size(44, 14);
            this->fcgLBSubpel->TabIndex = 195;
            this->fcgLBSubpel->Text = L"Subpel";
            // 
            // fcgCXEnableRestortionFiltering
            // 
            this->fcgCXEnableRestortionFiltering->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableRestortionFiltering->FormattingEnabled = true;
            this->fcgCXEnableRestortionFiltering->Location = System::Drawing::Point(165, 170);
            this->fcgCXEnableRestortionFiltering->Name = L"fcgCXEnableRestortionFiltering";
            this->fcgCXEnableRestortionFiltering->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableRestortionFiltering->TabIndex = 21;
            this->fcgCXEnableRestortionFiltering->Tag = L"reCmd";
            // 
            // fcgLBEnableRestortionFiltering
            // 
            this->fcgLBEnableRestortionFiltering->AutoSize = true;
            this->fcgLBEnableRestortionFiltering->Location = System::Drawing::Point(15, 173);
            this->fcgLBEnableRestortionFiltering->Name = L"fcgLBEnableRestortionFiltering";
            this->fcgLBEnableRestortionFiltering->Size = System::Drawing::Size(96, 14);
            this->fcgLBEnableRestortionFiltering->TabIndex = 189;
            this->fcgLBEnableRestortionFiltering->Text = L"RestorationFilter";
            // 
            // fcgCXEnableSpatialSSEfl
            // 
            this->fcgCXEnableSpatialSSEfl->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableSpatialSSEfl->FormattingEnabled = true;
            this->fcgCXEnableSpatialSSEfl->Location = System::Drawing::Point(165, 300);
            this->fcgCXEnableSpatialSSEfl->Name = L"fcgCXEnableSpatialSSEfl";
            this->fcgCXEnableSpatialSSEfl->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableSpatialSSEfl->TabIndex = 26;
            this->fcgCXEnableSpatialSSEfl->Tag = L"reCmd";
            // 
            // fcgLBEnableSpatialSSEfl
            // 
            this->fcgLBEnableSpatialSSEfl->AutoSize = true;
            this->fcgLBEnableSpatialSSEfl->Location = System::Drawing::Point(15, 303);
            this->fcgLBEnableSpatialSSEfl->Name = L"fcgLBEnableSpatialSSEfl";
            this->fcgLBEnableSpatialSSEfl->Size = System::Drawing::Size(71, 14);
            this->fcgLBEnableSpatialSSEfl->TabIndex = 187;
            this->fcgLBEnableSpatialSSEfl->Text = L"SpatialSSEfl";
            // 
            // fcgNUCDEFLevel
            // 
            this->fcgNUCDEFLevel->Location = System::Drawing::Point(525, 280);
            this->fcgNUCDEFLevel->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUCDEFLevel->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
            this->fcgNUCDEFLevel->Name = L"fcgNUCDEFLevel";
            this->fcgNUCDEFLevel->Size = System::Drawing::Size(64, 21);
            this->fcgNUCDEFLevel->TabIndex = 72;
            this->fcgNUCDEFLevel->Tag = L"reCmd";
            this->fcgNUCDEFLevel->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBCDEFLevel
            // 
            this->fcgLBCDEFLevel->AutoSize = true;
            this->fcgLBCDEFLevel->Location = System::Drawing::Point(375, 282);
            this->fcgLBCDEFLevel->Name = L"fcgLBCDEFLevel";
            this->fcgLBCDEFLevel->Size = System::Drawing::Size(62, 14);
            this->fcgLBCDEFLevel->TabIndex = 181;
            this->fcgLBCDEFLevel->Text = L"CDEFLevel";
            // 
            // fcgCXWnFilterMode
            // 
            this->fcgCXWnFilterMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXWnFilterMode->FormattingEnabled = true;
            this->fcgCXWnFilterMode->Location = System::Drawing::Point(165, 222);
            this->fcgCXWnFilterMode->Name = L"fcgCXWnFilterMode";
            this->fcgCXWnFilterMode->Size = System::Drawing::Size(118, 22);
            this->fcgCXWnFilterMode->TabIndex = 23;
            this->fcgCXWnFilterMode->Tag = L"reCmd";
            // 
            // fcgLBWnFilterMode
            // 
            this->fcgLBWnFilterMode->AutoSize = true;
            this->fcgLBWnFilterMode->Location = System::Drawing::Point(15, 225);
            this->fcgLBWnFilterMode->Name = L"fcgLBWnFilterMode";
            this->fcgLBWnFilterMode->Size = System::Drawing::Size(101, 14);
            this->fcgLBWnFilterMode->TabIndex = 179;
            this->fcgLBWnFilterMode->Text = L"WienerFilterMode";
            // 
            // fcgCXSgFilterMode
            // 
            this->fcgCXSgFilterMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXSgFilterMode->FormattingEnabled = true;
            this->fcgCXSgFilterMode->Location = System::Drawing::Point(165, 196);
            this->fcgCXSgFilterMode->Name = L"fcgCXSgFilterMode";
            this->fcgCXSgFilterMode->Size = System::Drawing::Size(118, 22);
            this->fcgCXSgFilterMode->TabIndex = 22;
            this->fcgCXSgFilterMode->Tag = L"reCmd";
            // 
            // fcgLBSgFilterMode
            // 
            this->fcgLBSgFilterMode->AutoSize = true;
            this->fcgLBSgFilterMode->Location = System::Drawing::Point(14, 199);
            this->fcgLBSgFilterMode->Name = L"fcgLBSgFilterMode";
            this->fcgLBSgFilterMode->Size = System::Drawing::Size(121, 14);
            this->fcgLBSgFilterMode->TabIndex = 177;
            this->fcgLBSgFilterMode->Text = L"SelfGuidedFilterMode";
            // 
            // fcgLBVBVBufSize
            // 
            this->fcgLBVBVBufSize->AutoSize = true;
            this->fcgLBVBVBufSize->Location = System::Drawing::Point(416, 146);
            this->fcgLBVBVBufSize->Name = L"fcgLBVBVBufSize";
            this->fcgLBVBVBufSize->Size = System::Drawing::Size(70, 14);
            this->fcgLBVBVBufSize->TabIndex = 174;
            this->fcgLBVBVBufSize->Text = L"VBVBufSize";
            // 
            // fcgNUVBVBufSize
            // 
            this->fcgNUVBVBufSize->Location = System::Drawing::Point(527, 144);
            this->fcgNUVBVBufSize->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000000, 0, 0, 0 });
            this->fcgNUVBVBufSize->Name = L"fcgNUVBVBufSize";
            this->fcgNUVBVBufSize->Size = System::Drawing::Size(64, 21);
            this->fcgNUVBVBufSize->TabIndex = 55;
            this->fcgNUVBVBufSize->Tag = L"reCmd";
            this->fcgNUVBVBufSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBMaxQP
            // 
            this->fcgLBMaxQP->AutoSize = true;
            this->fcgLBMaxQP->Location = System::Drawing::Point(520, 365);
            this->fcgLBMaxQP->Name = L"fcgLBMaxQP";
            this->fcgLBMaxQP->Size = System::Drawing::Size(12, 14);
            this->fcgLBMaxQP->TabIndex = 172;
            this->fcgLBMaxQP->Text = L"-";
            // 
            // fcgNUMaxQP
            // 
            this->fcgNUMaxQP->Location = System::Drawing::Point(535, 363);
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
            this->fcgLBMinQP->Location = System::Drawing::Point(374, 365);
            this->fcgLBMinQP->Name = L"fcgLBMinQP";
            this->fcgLBMinQP->Size = System::Drawing::Size(71, 14);
            this->fcgLBMinQP->TabIndex = 170;
            this->fcgLBMinQP->Text = L"QP Min-Max";
            // 
            // fcgNUMinQP
            // 
            this->fcgNUMinQP->Location = System::Drawing::Point(452, 363);
            this->fcgNUMinQP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 63, 0, 0, 0 });
            this->fcgNUMinQP->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, System::Int32::MinValue });
            this->fcgNUMinQP->Name = L"fcgNUMinQP";
            this->fcgNUMinQP->Size = System::Drawing::Size(64, 21);
            this->fcgNUMinQP->TabIndex = 84;
            this->fcgNUMinQP->Tag = L"reCmd";
            this->fcgNUMinQP->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCBEnableGlobalMotion
            // 
            this->fcgCBEnableGlobalMotion->AutoSize = true;
            this->fcgCBEnableGlobalMotion->Location = System::Drawing::Point(517, 423);
            this->fcgCBEnableGlobalMotion->Name = L"fcgCBEnableGlobalMotion";
            this->fcgCBEnableGlobalMotion->Size = System::Drawing::Size(15, 14);
            this->fcgCBEnableGlobalMotion->TabIndex = 93;
            this->fcgCBEnableGlobalMotion->Tag = L"reCmd";
            this->fcgCBEnableGlobalMotion->UseVisualStyleBackColor = true;
            // 
            // fcgLBSQW
            // 
            this->fcgLBSQW->AutoSize = true;
            this->fcgLBSQW->Location = System::Drawing::Point(375, 255);
            this->fcgLBSQW->Name = L"fcgLBSQW";
            this->fcgLBSQW->Size = System::Drawing::Size(83, 14);
            this->fcgLBSQW->TabIndex = 131;
            this->fcgLBSQW->Text = L"square weight";
            // 
            // fcgNUSQW
            // 
            this->fcgNUSQW->Location = System::Drawing::Point(525, 253);
            this->fcgNUSQW->Name = L"fcgNUSQW";
            this->fcgNUSQW->Size = System::Drawing::Size(64, 21);
            this->fcgNUSQW->TabIndex = 71;
            this->fcgNUSQW->Tag = L"reCmd";
            this->fcgNUSQW->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCXEnableRedunduntBLK
            // 
            this->fcgCXEnableRedunduntBLK->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableRedunduntBLK->FormattingEnabled = true;
            this->fcgCXEnableRedunduntBLK->Location = System::Drawing::Point(165, 274);
            this->fcgCXEnableRedunduntBLK->Name = L"fcgCXEnableRedunduntBLK";
            this->fcgCXEnableRedunduntBLK->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableRedunduntBLK->TabIndex = 25;
            this->fcgCXEnableRedunduntBLK->Tag = L"reCmd";
            // 
            // fcgLBEnableRedunduntBLK
            // 
            this->fcgLBEnableRedunduntBLK->AutoSize = true;
            this->fcgLBEnableRedunduntBLK->Location = System::Drawing::Point(15, 277);
            this->fcgLBEnableRedunduntBLK->Name = L"fcgLBEnableRedunduntBLK";
            this->fcgLBEnableRedunduntBLK->Size = System::Drawing::Size(95, 14);
            this->fcgLBEnableRedunduntBLK->TabIndex = 106;
            this->fcgLBEnableRedunduntBLK->Text = L"RedundantBlock";
            // 
            // fcgCXEnableMfmv
            // 
            this->fcgCXEnableMfmv->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableMfmv->FormattingEnabled = true;
            this->fcgCXEnableMfmv->Location = System::Drawing::Point(165, 248);
            this->fcgCXEnableMfmv->Name = L"fcgCXEnableMfmv";
            this->fcgCXEnableMfmv->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableMfmv->TabIndex = 24;
            this->fcgCXEnableMfmv->Tag = L"reCmd";
            // 
            // fcgLBMfmv
            // 
            this->fcgLBMfmv->AutoSize = true;
            this->fcgLBMfmv->Location = System::Drawing::Point(15, 251);
            this->fcgLBMfmv->Name = L"fcgLBMfmv";
            this->fcgLBMfmv->Size = System::Drawing::Size(86, 14);
            this->fcgLBMfmv->TabIndex = 104;
            this->fcgLBMfmv->Text = L"MotionFieldMV";
            // 
            // fcgLBAQ
            // 
            this->fcgLBAQ->AutoSize = true;
            this->fcgLBAQ->Location = System::Drawing::Point(15, 147);
            this->fcgLBAQ->Name = L"fcgLBAQ";
            this->fcgLBAQ->Size = System::Drawing::Size(22, 14);
            this->fcgLBAQ->TabIndex = 88;
            this->fcgLBAQ->Text = L"AQ";
            // 
            // fcgCXAQ
            // 
            this->fcgCXAQ->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXAQ->FormattingEnabled = true;
            this->fcgCXAQ->Location = System::Drawing::Point(165, 144);
            this->fcgCXAQ->Name = L"fcgCXAQ";
            this->fcgCXAQ->Size = System::Drawing::Size(118, 22);
            this->fcgCXAQ->TabIndex = 20;
            this->fcgCXAQ->Tag = L"reCmd";
            // 
            // fcgCBUseDefaultMeHme
            // 
            this->fcgCBUseDefaultMeHme->AutoSize = true;
            this->fcgCBUseDefaultMeHme->Location = System::Drawing::Point(517, 447);
            this->fcgCBUseDefaultMeHme->Name = L"fcgCBUseDefaultMeHme";
            this->fcgCBUseDefaultMeHme->Size = System::Drawing::Size(15, 14);
            this->fcgCBUseDefaultMeHme->TabIndex = 95;
            this->fcgCBUseDefaultMeHme->Tag = L"reCmd";
            this->fcgCBUseDefaultMeHme->UseVisualStyleBackColor = true;
            // 
            // fcgLBHierarchicalLevels
            // 
            this->fcgLBHierarchicalLevels->AutoSize = true;
            this->fcgLBHierarchicalLevels->Location = System::Drawing::Point(375, 228);
            this->fcgLBHierarchicalLevels->Name = L"fcgLBHierarchicalLevels";
            this->fcgLBHierarchicalLevels->Size = System::Drawing::Size(103, 14);
            this->fcgLBHierarchicalLevels->TabIndex = 85;
            this->fcgLBHierarchicalLevels->Text = L"hierarchical levels";
            // 
            // fcgLBSearch2
            // 
            this->fcgLBSearch2->AutoSize = true;
            this->fcgLBSearch2->Location = System::Drawing::Point(519, 338);
            this->fcgLBSearch2->Name = L"fcgLBSearch2";
            this->fcgLBSearch2->Size = System::Drawing::Size(13, 14);
            this->fcgLBSearch2->TabIndex = 83;
            this->fcgLBSearch2->Text = L"x";
            // 
            // fcgLBTile2
            // 
            this->fcgLBTile2->AutoSize = true;
            this->fcgLBTile2->Location = System::Drawing::Point(519, 311);
            this->fcgLBTile2->Name = L"fcgLBTile2";
            this->fcgLBTile2->Size = System::Drawing::Size(13, 14);
            this->fcgLBTile2->TabIndex = 82;
            this->fcgLBTile2->Text = L"x";
            // 
            // fcgNUSearchH
            // 
            this->fcgNUSearchH->Location = System::Drawing::Point(535, 336);
            this->fcgNUSearchH->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 256, 0, 0, 0 });
            this->fcgNUSearchH->Name = L"fcgNUSearchH";
            this->fcgNUSearchH->Size = System::Drawing::Size(64, 21);
            this->fcgNUSearchH->TabIndex = 83;
            this->fcgNUSearchH->Tag = L"reCmd";
            this->fcgNUSearchH->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBSearch
            // 
            this->fcgLBSearch->AutoSize = true;
            this->fcgLBSearch->Location = System::Drawing::Point(374, 338);
            this->fcgLBSearch->Name = L"fcgLBSearch";
            this->fcgLBSearch->Size = System::Drawing::Size(42, 14);
            this->fcgLBSearch->TabIndex = 80;
            this->fcgLBSearch->Text = L"search";
            // 
            // fcgNUSearchW
            // 
            this->fcgNUSearchW->Location = System::Drawing::Point(452, 336);
            this->fcgNUSearchW->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 256, 0, 0, 0 });
            this->fcgNUSearchW->Name = L"fcgNUSearchW";
            this->fcgNUSearchW->Size = System::Drawing::Size(64, 21);
            this->fcgNUSearchW->TabIndex = 82;
            this->fcgNUSearchW->Tag = L"reCmd";
            this->fcgNUSearchW->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgNUTileColumns
            // 
            this->fcgNUTileColumns->Location = System::Drawing::Point(535, 308);
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
            this->fcgLBTile->Location = System::Drawing::Point(375, 311);
            this->fcgLBTile->Name = L"fcgLBTile";
            this->fcgLBTile->Size = System::Drawing::Size(23, 14);
            this->fcgLBTile->TabIndex = 77;
            this->fcgLBTile->Text = L"tile";
            // 
            // fcgNUTileRows
            // 
            this->fcgNUTileRows->Location = System::Drawing::Point(452, 308);
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
            this->fcgLBIntraRefreshType->Location = System::Drawing::Point(416, 94);
            this->fcgLBIntraRefreshType->Name = L"fcgLBIntraRefreshType";
            this->fcgLBIntraRefreshType->Size = System::Drawing::Size(101, 14);
            this->fcgLBIntraRefreshType->TabIndex = 71;
            this->fcgLBIntraRefreshType->Text = L"intra refresh type";
            // 
            // fcgNUIntraRefreshType
            // 
            this->fcgNUIntraRefreshType->Location = System::Drawing::Point(527, 92);
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
            this->fcgLBKeyint->Location = System::Drawing::Point(416, 67);
            this->fcgLBKeyint->Name = L"fcgLBKeyint";
            this->fcgLBKeyint->Size = System::Drawing::Size(39, 14);
            this->fcgLBKeyint->TabIndex = 69;
            this->fcgLBKeyint->Text = L"keyint";
            // 
            // fcgNUKeyint
            // 
            this->fcgNUKeyint->Location = System::Drawing::Point(527, 65);
            this->fcgNUKeyint->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
            this->fcgNUKeyint->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, System::Int32::MinValue });
            this->fcgNUKeyint->Name = L"fcgNUKeyint";
            this->fcgNUKeyint->Size = System::Drawing::Size(64, 21);
            this->fcgNUKeyint->TabIndex = 52;
            this->fcgNUKeyint->Tag = L"reCmd";
            this->fcgNUKeyint->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBLookahead
            // 
            this->fcgLBLookahead->AutoSize = true;
            this->fcgLBLookahead->Location = System::Drawing::Point(416, 119);
            this->fcgLBLookahead->Name = L"fcgLBLookahead";
            this->fcgLBLookahead->Size = System::Drawing::Size(62, 14);
            this->fcgLBLookahead->TabIndex = 65;
            this->fcgLBLookahead->Text = L"lookahead";
            // 
            // fcgNULookaheadDistance
            // 
            this->fcgNULookaheadDistance->Location = System::Drawing::Point(527, 117);
            this->fcgNULookaheadDistance->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
            this->fcgNULookaheadDistance->Name = L"fcgNULookaheadDistance";
            this->fcgNULookaheadDistance->Size = System::Drawing::Size(64, 21);
            this->fcgNULookaheadDistance->TabIndex = 54;
            this->fcgNULookaheadDistance->Tag = L"reCmd";
            this->fcgNULookaheadDistance->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBThreads
            // 
            this->fcgLBThreads->AutoSize = true;
            this->fcgLBThreads->Location = System::Drawing::Point(417, 40);
            this->fcgLBThreads->Name = L"fcgLBThreads";
            this->fcgLBThreads->Size = System::Drawing::Size(47, 14);
            this->fcgLBThreads->TabIndex = 51;
            this->fcgLBThreads->Text = L"threads";
            // 
            // fcgNUThreads
            // 
            this->fcgNUThreads->Location = System::Drawing::Point(527, 38);
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
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXTFLevel);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBSTATUS);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgTXStatusFile);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgBTStatusFile);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBBiasPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUBiasPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBOverShootPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUOverShootPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBUnderShootPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUUnderShootPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBMaxSectionPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUMaxSectionPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBMinSectionPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUMinSectionPct);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXMrpLevel);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBMrpLevel);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXObmcLevel);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBObmcLevel);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXExtBlock);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBExtBlock);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBTFLevel);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXUMV);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBUMV);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXPalette);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBPalette);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXPredMe);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBPredMe);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXSCM);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBScm);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXCompund);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBCompund);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXRDOQ);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBRDOQ);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXBipred3x3);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBBipred3x3);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcggroupBoxColorMatrix);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcggroupBoxAepectRatio);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnableIntraEdgeSkp);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableIntraEdgeSkp);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnableIntraEdgeFilter);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableIntraEdgeFilter);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnableInterIntraComp);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableInterIntraComp);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnablePaeth);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnablePaeth);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnableSmooth);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableSmooth);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXIntraBCMode);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBIntraBCMode);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnableIntraAngleDelta);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableIntraAngleDelta);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXHighBitDepthModeDecision);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBHighBitDepthModeDecision);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgCXEnableFilterIntra);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBEnableFilterIntra);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBAltRefNframes);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUAltRefNframes);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgLBAltRefStrength);
            this->fcgtabPageSVTAV1_2->Controls->Add(this->fcgNUAltRefStrength);
            this->fcgtabPageSVTAV1_2->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageSVTAV1_2->Name = L"fcgtabPageSVTAV1_2";
            this->fcgtabPageSVTAV1_2->Size = System::Drawing::Size(608, 493);
            this->fcgtabPageSVTAV1_2->TabIndex = 4;
            this->fcgtabPageSVTAV1_2->Text = L"SVT-AV1 (2)";
            this->fcgtabPageSVTAV1_2->UseVisualStyleBackColor = true;
            // 
            // fcgCXTFLevel
            // 
            this->fcgCXTFLevel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXTFLevel->FormattingEnabled = true;
            this->fcgCXTFLevel->Location = System::Drawing::Point(480, 11);
            this->fcgCXTFLevel->Name = L"fcgCXTFLevel";
            this->fcgCXTFLevel->Size = System::Drawing::Size(118, 22);
            this->fcgCXTFLevel->TabIndex = 120;
            this->fcgCXTFLevel->Tag = L"reCmd";
            // 
            // fcgLBSTATUS
            // 
            this->fcgLBSTATUS->AutoSize = true;
            this->fcgLBSTATUS->Location = System::Drawing::Point(10, 465);
            this->fcgLBSTATUS->Name = L"fcgLBSTATUS";
            this->fcgLBSTATUS->Size = System::Drawing::Size(78, 14);
            this->fcgLBSTATUS->TabIndex = 236;
            this->fcgLBSTATUS->Text = L"ステータスファイル";
            // 
            // fcgTXStatusFile
            // 
            this->fcgTXStatusFile->Location = System::Drawing::Point(105, 462);
            this->fcgTXStatusFile->Name = L"fcgTXStatusFile";
            this->fcgTXStatusFile->Size = System::Drawing::Size(253, 21);
            this->fcgTXStatusFile->TabIndex = 160;
            this->fcgTXStatusFile->Tag = L"reCmd";
            // 
            // fcgBTStatusFile
            // 
            this->fcgBTStatusFile->Location = System::Drawing::Point(358, 461);
            this->fcgBTStatusFile->Name = L"fcgBTStatusFile";
            this->fcgBTStatusFile->Size = System::Drawing::Size(27, 22);
            this->fcgBTStatusFile->TabIndex = 161;
            this->fcgBTStatusFile->Text = L"...";
            this->fcgBTStatusFile->UseVisualStyleBackColor = true;
            this->fcgBTStatusFile->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTStatusFile_Click);
            // 
            // fcgLBBiasPct
            // 
            this->fcgLBBiasPct->AutoSize = true;
            this->fcgLBBiasPct->Location = System::Drawing::Point(330, 150);
            this->fcgLBBiasPct->Name = L"fcgLBBiasPct";
            this->fcgLBBiasPct->Size = System::Drawing::Size(76, 14);
            this->fcgLBBiasPct->TabIndex = 233;
            this->fcgLBBiasPct->Text = L"VBR Bias Pct";
            // 
            // fcgNUBiasPct
            // 
            this->fcgNUBiasPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUBiasPct->Location = System::Drawing::Point(480, 148);
            this->fcgNUBiasPct->Name = L"fcgNUBiasPct";
            this->fcgNUBiasPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUBiasPct->TabIndex = 126;
            this->fcgNUBiasPct->Tag = L"reCmd";
            this->fcgNUBiasPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBOverShootPct
            // 
            this->fcgLBOverShootPct->AutoSize = true;
            this->fcgLBOverShootPct->Location = System::Drawing::Point(330, 253);
            this->fcgLBOverShootPct->Name = L"fcgLBOverShootPct";
            this->fcgLBOverShootPct->Size = System::Drawing::Size(81, 14);
            this->fcgLBOverShootPct->TabIndex = 231;
            this->fcgLBOverShootPct->Text = L"OverShootPct";
            // 
            // fcgNUOverShootPct
            // 
            this->fcgNUOverShootPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUOverShootPct->Location = System::Drawing::Point(480, 251);
            this->fcgNUOverShootPct->Name = L"fcgNUOverShootPct";
            this->fcgNUOverShootPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUOverShootPct->TabIndex = 130;
            this->fcgNUOverShootPct->Tag = L"reCmd";
            this->fcgNUOverShootPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBUnderShootPct
            // 
            this->fcgLBUnderShootPct->AutoSize = true;
            this->fcgLBUnderShootPct->Location = System::Drawing::Point(330, 227);
            this->fcgLBUnderShootPct->Name = L"fcgLBUnderShootPct";
            this->fcgLBUnderShootPct->Size = System::Drawing::Size(89, 14);
            this->fcgLBUnderShootPct->TabIndex = 229;
            this->fcgLBUnderShootPct->Text = L"UnderShootPct";
            // 
            // fcgNUUnderShootPct
            // 
            this->fcgNUUnderShootPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            this->fcgNUUnderShootPct->Location = System::Drawing::Point(480, 225);
            this->fcgNUUnderShootPct->Name = L"fcgNUUnderShootPct";
            this->fcgNUUnderShootPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUUnderShootPct->TabIndex = 129;
            this->fcgNUUnderShootPct->Tag = L"reCmd";
            this->fcgNUUnderShootPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBMaxSectionPct
            // 
            this->fcgLBMaxSectionPct->AutoSize = true;
            this->fcgLBMaxSectionPct->Location = System::Drawing::Point(330, 201);
            this->fcgLBMaxSectionPct->Name = L"fcgLBMaxSectionPct";
            this->fcgLBMaxSectionPct->Size = System::Drawing::Size(85, 14);
            this->fcgLBMaxSectionPct->TabIndex = 227;
            this->fcgLBMaxSectionPct->Text = L"MaxSectionPct";
            // 
            // fcgNUMaxSectionPct
            // 
            this->fcgNUMaxSectionPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->fcgNUMaxSectionPct->Location = System::Drawing::Point(480, 199);
            this->fcgNUMaxSectionPct->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
            this->fcgNUMaxSectionPct->Name = L"fcgNUMaxSectionPct";
            this->fcgNUMaxSectionPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUMaxSectionPct->TabIndex = 128;
            this->fcgNUMaxSectionPct->Tag = L"reCmd";
            this->fcgNUMaxSectionPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBMinSectionPct
            // 
            this->fcgLBMinSectionPct->AutoSize = true;
            this->fcgLBMinSectionPct->Location = System::Drawing::Point(330, 175);
            this->fcgLBMinSectionPct->Name = L"fcgLBMinSectionPct";
            this->fcgLBMinSectionPct->Size = System::Drawing::Size(83, 14);
            this->fcgLBMinSectionPct->TabIndex = 225;
            this->fcgLBMinSectionPct->Text = L"MinSectionPct";
            // 
            // fcgNUMinSectionPct
            // 
            this->fcgNUMinSectionPct->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->fcgNUMinSectionPct->Location = System::Drawing::Point(480, 173);
            this->fcgNUMinSectionPct->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
            this->fcgNUMinSectionPct->Name = L"fcgNUMinSectionPct";
            this->fcgNUMinSectionPct->Size = System::Drawing::Size(64, 21);
            this->fcgNUMinSectionPct->TabIndex = 127;
            this->fcgNUMinSectionPct->Tag = L"reCmd";
            this->fcgNUMinSectionPct->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgCXMrpLevel
            // 
            this->fcgCXMrpLevel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMrpLevel->FormattingEnabled = true;
            this->fcgCXMrpLevel->Location = System::Drawing::Point(480, 92);
            this->fcgCXMrpLevel->Name = L"fcgCXMrpLevel";
            this->fcgCXMrpLevel->Size = System::Drawing::Size(118, 22);
            this->fcgCXMrpLevel->TabIndex = 124;
            this->fcgCXMrpLevel->Tag = L"reCmd";
            // 
            // fcgLBMrpLevel
            // 
            this->fcgLBMrpLevel->AutoSize = true;
            this->fcgLBMrpLevel->Location = System::Drawing::Point(330, 95);
            this->fcgLBMrpLevel->Name = L"fcgLBMrpLevel";
            this->fcgLBMrpLevel->Size = System::Drawing::Size(130, 14);
            this->fcgLBMrpLevel->TabIndex = 222;
            this->fcgLBMrpLevel->Text = L"MultiReferencePictures";
            // 
            // fcgCXObmcLevel
            // 
            this->fcgCXObmcLevel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXObmcLevel->FormattingEnabled = true;
            this->fcgCXObmcLevel->Location = System::Drawing::Point(480, 118);
            this->fcgCXObmcLevel->Name = L"fcgCXObmcLevel";
            this->fcgCXObmcLevel->Size = System::Drawing::Size(118, 22);
            this->fcgCXObmcLevel->TabIndex = 125;
            this->fcgCXObmcLevel->Tag = L"reCmd";
            // 
            // fcgLBObmcLevel
            // 
            this->fcgLBObmcLevel->AutoSize = true;
            this->fcgLBObmcLevel->Location = System::Drawing::Point(330, 121);
            this->fcgLBObmcLevel->Name = L"fcgLBObmcLevel";
            this->fcgLBObmcLevel->Size = System::Drawing::Size(70, 14);
            this->fcgLBObmcLevel->TabIndex = 220;
            this->fcgLBObmcLevel->Text = L"Obmc Level";
            // 
            // fcgCXExtBlock
            // 
            this->fcgCXExtBlock->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXExtBlock->FormattingEnabled = true;
            this->fcgCXExtBlock->Location = System::Drawing::Point(167, 298);
            this->fcgCXExtBlock->Name = L"fcgCXExtBlock";
            this->fcgCXExtBlock->Size = System::Drawing::Size(118, 22);
            this->fcgCXExtBlock->TabIndex = 112;
            this->fcgCXExtBlock->Tag = L"reCmd";
            // 
            // fcgLBExtBlock
            // 
            this->fcgLBExtBlock->AutoSize = true;
            this->fcgLBExtBlock->Location = System::Drawing::Point(10, 301);
            this->fcgLBExtBlock->Name = L"fcgLBExtBlock";
            this->fcgLBExtBlock->Size = System::Drawing::Size(53, 14);
            this->fcgLBExtBlock->TabIndex = 215;
            this->fcgLBExtBlock->Text = L"ExtBlock";
            // 
            // fcgLBTFLevel
            // 
            this->fcgLBTFLevel->AutoSize = true;
            this->fcgLBTFLevel->Location = System::Drawing::Point(330, 14);
            this->fcgLBTFLevel->Name = L"fcgLBTFLevel";
            this->fcgLBTFLevel->Size = System::Drawing::Size(66, 14);
            this->fcgLBTFLevel->TabIndex = 213;
            this->fcgLBTFLevel->Text = L"AltRefLevel";
            // 
            // fcgCXUMV
            // 
            this->fcgCXUMV->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXUMV->FormattingEnabled = true;
            this->fcgCXUMV->Location = System::Drawing::Point(167, 429);
            this->fcgCXUMV->Name = L"fcgCXUMV";
            this->fcgCXUMV->Size = System::Drawing::Size(118, 22);
            this->fcgCXUMV->TabIndex = 117;
            this->fcgCXUMV->Tag = L"reCmd";
            // 
            // fcgLBUMV
            // 
            this->fcgLBUMV->AutoSize = true;
            this->fcgLBUMV->Location = System::Drawing::Point(10, 432);
            this->fcgLBUMV->Name = L"fcgLBUMV";
            this->fcgLBUMV->Size = System::Drawing::Size(90, 14);
            this->fcgLBUMV->TabIndex = 211;
            this->fcgLBUMV->Text = L"UnrestrictedMV";
            // 
            // fcgCXPalette
            // 
            this->fcgCXPalette->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXPalette->FormattingEnabled = true;
            this->fcgCXPalette->Location = System::Drawing::Point(167, 403);
            this->fcgCXPalette->Name = L"fcgCXPalette";
            this->fcgCXPalette->Size = System::Drawing::Size(118, 22);
            this->fcgCXPalette->TabIndex = 116;
            this->fcgCXPalette->Tag = L"reCmd";
            // 
            // fcgLBPalette
            // 
            this->fcgLBPalette->AutoSize = true;
            this->fcgLBPalette->Location = System::Drawing::Point(10, 406);
            this->fcgLBPalette->Name = L"fcgLBPalette";
            this->fcgLBPalette->Size = System::Drawing::Size(72, 14);
            this->fcgLBPalette->TabIndex = 209;
            this->fcgLBPalette->Text = L"PaletteMode";
            // 
            // fcgCXPredMe
            // 
            this->fcgCXPredMe->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXPredMe->FormattingEnabled = true;
            this->fcgCXPredMe->Location = System::Drawing::Point(167, 219);
            this->fcgCXPredMe->Name = L"fcgCXPredMe";
            this->fcgCXPredMe->Size = System::Drawing::Size(118, 22);
            this->fcgCXPredMe->TabIndex = 109;
            this->fcgCXPredMe->Tag = L"reCmd";
            // 
            // fcgLBPredMe
            // 
            this->fcgLBPredMe->AutoSize = true;
            this->fcgLBPredMe->Location = System::Drawing::Point(10, 222);
            this->fcgLBPredMe->Name = L"fcgLBPredMe";
            this->fcgLBPredMe->Size = System::Drawing::Size(75, 14);
            this->fcgLBPredMe->TabIndex = 205;
            this->fcgLBPredMe->Text = L"PredictiveMe";
            // 
            // fcgCXSCM
            // 
            this->fcgCXSCM->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXSCM->FormattingEnabled = true;
            this->fcgCXSCM->Location = System::Drawing::Point(167, 325);
            this->fcgCXSCM->Name = L"fcgCXSCM";
            this->fcgCXSCM->Size = System::Drawing::Size(118, 22);
            this->fcgCXSCM->TabIndex = 113;
            this->fcgCXSCM->Tag = L"reCmd";
            // 
            // fcgLBScm
            // 
            this->fcgLBScm->AutoSize = true;
            this->fcgLBScm->Location = System::Drawing::Point(10, 328);
            this->fcgLBScm->Name = L"fcgLBScm";
            this->fcgLBScm->Size = System::Drawing::Size(115, 14);
            this->fcgLBScm->TabIndex = 203;
            this->fcgLBScm->Text = L"ScreenContentMode";
            // 
            // fcgCXCompund
            // 
            this->fcgCXCompund->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXCompund->FormattingEnabled = true;
            this->fcgCXCompund->Location = System::Drawing::Point(167, 271);
            this->fcgCXCompund->Name = L"fcgCXCompund";
            this->fcgCXCompund->Size = System::Drawing::Size(118, 22);
            this->fcgCXCompund->TabIndex = 111;
            this->fcgCXCompund->Tag = L"reCmd";
            // 
            // fcgLBCompund
            // 
            this->fcgLBCompund->AutoSize = true;
            this->fcgLBCompund->Location = System::Drawing::Point(10, 274);
            this->fcgLBCompund->Name = L"fcgLBCompund";
            this->fcgLBCompund->Size = System::Drawing::Size(67, 14);
            this->fcgLBCompund->TabIndex = 201;
            this->fcgLBCompund->Text = L"Compound";
            // 
            // fcgCXRDOQ
            // 
            this->fcgCXRDOQ->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXRDOQ->FormattingEnabled = true;
            this->fcgCXRDOQ->Location = System::Drawing::Point(167, 141);
            this->fcgCXRDOQ->Name = L"fcgCXRDOQ";
            this->fcgCXRDOQ->Size = System::Drawing::Size(118, 22);
            this->fcgCXRDOQ->TabIndex = 106;
            this->fcgCXRDOQ->Tag = L"reCmd";
            // 
            // fcgLBRDOQ
            // 
            this->fcgLBRDOQ->AutoSize = true;
            this->fcgLBRDOQ->Location = System::Drawing::Point(10, 144);
            this->fcgLBRDOQ->Name = L"fcgLBRDOQ";
            this->fcgLBRDOQ->Size = System::Drawing::Size(39, 14);
            this->fcgLBRDOQ->TabIndex = 199;
            this->fcgLBRDOQ->Text = L"RDOQ";
            // 
            // fcgCXBipred3x3
            // 
            this->fcgCXBipred3x3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXBipred3x3->FormattingEnabled = true;
            this->fcgCXBipred3x3->Location = System::Drawing::Point(167, 245);
            this->fcgCXBipred3x3->Name = L"fcgCXBipred3x3";
            this->fcgCXBipred3x3->Size = System::Drawing::Size(118, 22);
            this->fcgCXBipred3x3->TabIndex = 110;
            this->fcgCXBipred3x3->Tag = L"reCmd";
            // 
            // fcgLBBipred3x3
            // 
            this->fcgLBBipred3x3->AutoSize = true;
            this->fcgLBBipred3x3->Location = System::Drawing::Point(10, 248);
            this->fcgLBBipred3x3->Name = L"fcgLBBipred3x3";
            this->fcgLBBipred3x3->Size = System::Drawing::Size(110, 14);
            this->fcgLBBipred3x3->TabIndex = 197;
            this->fcgLBBipred3x3->Text = L"Bi-predictional 3x3";
            // 
            // fcggroupBoxColorMatrix
            // 
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXInputRange);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBInputRange);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXTransfer);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXColorPrim);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgCXColorMatrix);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBTransfer);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBColorPrim);
            this->fcggroupBoxColorMatrix->Controls->Add(this->fcgLBColorMatrix);
            this->fcggroupBoxColorMatrix->Location = System::Drawing::Point(489, 458);
            this->fcggroupBoxColorMatrix->Name = L"fcggroupBoxColorMatrix";
            this->fcggroupBoxColorMatrix->Size = System::Drawing::Size(218, 145);
            this->fcggroupBoxColorMatrix->TabIndex = 196;
            this->fcggroupBoxColorMatrix->TabStop = false;
            this->fcggroupBoxColorMatrix->Text = L"色空間";
            this->fcggroupBoxColorMatrix->Visible = false;
            // 
            // fcgCXInputRange
            // 
            this->fcgCXInputRange->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXInputRange->FormattingEnabled = true;
            this->fcgCXInputRange->Location = System::Drawing::Point(82, 114);
            this->fcgCXInputRange->Name = L"fcgCXInputRange";
            this->fcgCXInputRange->Size = System::Drawing::Size(131, 22);
            this->fcgCXInputRange->TabIndex = 4;
            this->fcgCXInputRange->Tag = L"reCmd";
            // 
            // fcgLBInputRange
            // 
            this->fcgLBInputRange->AutoSize = true;
            this->fcgLBInputRange->Location = System::Drawing::Point(8, 117);
            this->fcgLBInputRange->Name = L"fcgLBInputRange";
            this->fcgLBInputRange->Size = System::Drawing::Size(70, 14);
            this->fcgLBInputRange->TabIndex = 3;
            this->fcgLBInputRange->Text = L"input range";
            // 
            // fcgCXTransfer
            // 
            this->fcgCXTransfer->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXTransfer->FormattingEnabled = true;
            this->fcgCXTransfer->Location = System::Drawing::Point(82, 83);
            this->fcgCXTransfer->Name = L"fcgCXTransfer";
            this->fcgCXTransfer->Size = System::Drawing::Size(131, 22);
            this->fcgCXTransfer->TabIndex = 2;
            this->fcgCXTransfer->Tag = L"reCmd";
            // 
            // fcgCXColorPrim
            // 
            this->fcgCXColorPrim->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXColorPrim->FormattingEnabled = true;
            this->fcgCXColorPrim->Location = System::Drawing::Point(82, 51);
            this->fcgCXColorPrim->Name = L"fcgCXColorPrim";
            this->fcgCXColorPrim->Size = System::Drawing::Size(131, 22);
            this->fcgCXColorPrim->TabIndex = 1;
            this->fcgCXColorPrim->Tag = L"reCmd";
            // 
            // fcgCXColorMatrix
            // 
            this->fcgCXColorMatrix->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXColorMatrix->FormattingEnabled = true;
            this->fcgCXColorMatrix->Location = System::Drawing::Point(82, 20);
            this->fcgCXColorMatrix->Name = L"fcgCXColorMatrix";
            this->fcgCXColorMatrix->Size = System::Drawing::Size(131, 22);
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
            // fcggroupBoxAepectRatio
            // 
            this->fcggroupBoxAepectRatio->Controls->Add(this->fcgNUAspectRatioY);
            this->fcggroupBoxAepectRatio->Controls->Add(this->fcgLBAspectRatio);
            this->fcggroupBoxAepectRatio->Controls->Add(this->fcgNUAspectRatioX);
            this->fcggroupBoxAepectRatio->Controls->Add(this->fcgCXAspectRatio);
            this->fcggroupBoxAepectRatio->Location = System::Drawing::Point(555, 453);
            this->fcggroupBoxAepectRatio->Name = L"fcggroupBoxAepectRatio";
            this->fcggroupBoxAepectRatio->Size = System::Drawing::Size(205, 94);
            this->fcggroupBoxAepectRatio->TabIndex = 195;
            this->fcggroupBoxAepectRatio->TabStop = false;
            this->fcggroupBoxAepectRatio->Text = L"アスペクト比";
            this->fcggroupBoxAepectRatio->Visible = false;
            // 
            // fcgNUAspectRatioY
            // 
            this->fcgNUAspectRatioY->Location = System::Drawing::Point(126, 57);
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
            this->fcgLBAspectRatio->Location = System::Drawing::Point(108, 59);
            this->fcgLBAspectRatio->Name = L"fcgLBAspectRatio";
            this->fcgLBAspectRatio->Size = System::Drawing::Size(12, 14);
            this->fcgLBAspectRatio->TabIndex = 2;
            this->fcgLBAspectRatio->Text = L":";
            // 
            // fcgNUAspectRatioX
            // 
            this->fcgNUAspectRatioX->Location = System::Drawing::Point(42, 57);
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
            this->fcgCXAspectRatio->Location = System::Drawing::Point(15, 29);
            this->fcgCXAspectRatio->Name = L"fcgCXAspectRatio";
            this->fcgCXAspectRatio->Size = System::Drawing::Size(171, 22);
            this->fcgCXAspectRatio->TabIndex = 0;
            this->fcgCXAspectRatio->Tag = L"reCmd";
            // 
            // fcgCXEnableIntraEdgeSkp
            // 
            this->fcgCXEnableIntraEdgeSkp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableIntraEdgeSkp->FormattingEnabled = true;
            this->fcgCXEnableIntraEdgeSkp->Location = System::Drawing::Point(167, 11);
            this->fcgCXEnableIntraEdgeSkp->Name = L"fcgCXEnableIntraEdgeSkp";
            this->fcgCXEnableIntraEdgeSkp->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableIntraEdgeSkp->TabIndex = 101;
            this->fcgCXEnableIntraEdgeSkp->Tag = L"reCmd";
            // 
            // fcgLBEnableIntraEdgeSkp
            // 
            this->fcgLBEnableIntraEdgeSkp->AutoSize = true;
            this->fcgLBEnableIntraEdgeSkp->Location = System::Drawing::Point(10, 14);
            this->fcgLBEnableIntraEdgeSkp->Name = L"fcgLBEnableIntraEdgeSkp";
            this->fcgLBEnableIntraEdgeSkp->Size = System::Drawing::Size(113, 14);
            this->fcgLBEnableIntraEdgeSkp->TabIndex = 193;
            this->fcgLBEnableIntraEdgeSkp->Text = L"EdgeSkipAngleIntra";
            // 
            // fcgCXEnableIntraEdgeFilter
            // 
            this->fcgCXEnableIntraEdgeFilter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableIntraEdgeFilter->FormattingEnabled = true;
            this->fcgCXEnableIntraEdgeFilter->Location = System::Drawing::Point(167, 193);
            this->fcgCXEnableIntraEdgeFilter->Name = L"fcgCXEnableIntraEdgeFilter";
            this->fcgCXEnableIntraEdgeFilter->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableIntraEdgeFilter->TabIndex = 108;
            this->fcgCXEnableIntraEdgeFilter->Tag = L"reCmd";
            // 
            // fcgLBEnableIntraEdgeFilter
            // 
            this->fcgLBEnableIntraEdgeFilter->AutoSize = true;
            this->fcgLBEnableIntraEdgeFilter->Location = System::Drawing::Point(10, 196);
            this->fcgLBEnableIntraEdgeFilter->Name = L"fcgLBEnableIntraEdgeFilter";
            this->fcgLBEnableIntraEdgeFilter->Size = System::Drawing::Size(87, 14);
            this->fcgLBEnableIntraEdgeFilter->TabIndex = 191;
            this->fcgLBEnableIntraEdgeFilter->Text = L"IntraEdgeFilter";
            // 
            // fcgCXEnableInterIntraComp
            // 
            this->fcgCXEnableInterIntraComp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableInterIntraComp->FormattingEnabled = true;
            this->fcgCXEnableInterIntraComp->Location = System::Drawing::Point(167, 63);
            this->fcgCXEnableInterIntraComp->Name = L"fcgCXEnableInterIntraComp";
            this->fcgCXEnableInterIntraComp->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableInterIntraComp->TabIndex = 103;
            this->fcgCXEnableInterIntraComp->Tag = L"reCmd";
            // 
            // fcgLBEnableInterIntraComp
            // 
            this->fcgLBEnableInterIntraComp->AutoSize = true;
            this->fcgLBEnableInterIntraComp->Location = System::Drawing::Point(10, 66);
            this->fcgLBEnableInterIntraComp->Name = L"fcgLBEnableInterIntraComp";
            this->fcgLBEnableInterIntraComp->Size = System::Drawing::Size(119, 14);
            this->fcgLBEnableInterIntraComp->TabIndex = 189;
            this->fcgLBEnableInterIntraComp->Text = L"InterIntraCompound";
            // 
            // fcgCXEnablePaeth
            // 
            this->fcgCXEnablePaeth->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnablePaeth->FormattingEnabled = true;
            this->fcgCXEnablePaeth->Location = System::Drawing::Point(167, 89);
            this->fcgCXEnablePaeth->Name = L"fcgCXEnablePaeth";
            this->fcgCXEnablePaeth->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnablePaeth->TabIndex = 104;
            this->fcgCXEnablePaeth->Tag = L"reCmd";
            // 
            // fcgLBEnablePaeth
            // 
            this->fcgLBEnablePaeth->AutoSize = true;
            this->fcgLBEnablePaeth->Location = System::Drawing::Point(10, 92);
            this->fcgLBEnablePaeth->Name = L"fcgLBEnablePaeth";
            this->fcgLBEnablePaeth->Size = System::Drawing::Size(37, 14);
            this->fcgLBEnablePaeth->TabIndex = 165;
            this->fcgLBEnablePaeth->Text = L"Paeth";
            // 
            // fcgCXEnableSmooth
            // 
            this->fcgCXEnableSmooth->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableSmooth->FormattingEnabled = true;
            this->fcgCXEnableSmooth->Location = System::Drawing::Point(167, 115);
            this->fcgCXEnableSmooth->Name = L"fcgCXEnableSmooth";
            this->fcgCXEnableSmooth->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableSmooth->TabIndex = 105;
            this->fcgCXEnableSmooth->Tag = L"reCmd";
            // 
            // fcgLBEnableSmooth
            // 
            this->fcgLBEnableSmooth->AutoSize = true;
            this->fcgLBEnableSmooth->Location = System::Drawing::Point(10, 118);
            this->fcgLBEnableSmooth->Name = L"fcgLBEnableSmooth";
            this->fcgLBEnableSmooth->Size = System::Drawing::Size(50, 14);
            this->fcgLBEnableSmooth->TabIndex = 163;
            this->fcgLBEnableSmooth->Text = L"Smooth";
            // 
            // fcgCXIntraBCMode
            // 
            this->fcgCXIntraBCMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXIntraBCMode->FormattingEnabled = true;
            this->fcgCXIntraBCMode->Location = System::Drawing::Point(167, 351);
            this->fcgCXIntraBCMode->Name = L"fcgCXIntraBCMode";
            this->fcgCXIntraBCMode->Size = System::Drawing::Size(118, 22);
            this->fcgCXIntraBCMode->TabIndex = 114;
            this->fcgCXIntraBCMode->Tag = L"reCmd";
            // 
            // fcgLBIntraBCMode
            // 
            this->fcgLBIntraBCMode->AutoSize = true;
            this->fcgLBIntraBCMode->Location = System::Drawing::Point(10, 354);
            this->fcgLBIntraBCMode->Name = L"fcgLBIntraBCMode";
            this->fcgLBIntraBCMode->Size = System::Drawing::Size(76, 14);
            this->fcgLBIntraBCMode->TabIndex = 157;
            this->fcgLBIntraBCMode->Text = L"IntraBCMode";
            // 
            // fcgCXEnableIntraAngleDelta
            // 
            this->fcgCXEnableIntraAngleDelta->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableIntraAngleDelta->FormattingEnabled = true;
            this->fcgCXEnableIntraAngleDelta->Location = System::Drawing::Point(167, 37);
            this->fcgCXEnableIntraAngleDelta->Name = L"fcgCXEnableIntraAngleDelta";
            this->fcgCXEnableIntraAngleDelta->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableIntraAngleDelta->TabIndex = 102;
            this->fcgCXEnableIntraAngleDelta->Tag = L"reCmd";
            // 
            // fcgLBEnableIntraAngleDelta
            // 
            this->fcgLBEnableIntraAngleDelta->AutoSize = true;
            this->fcgLBEnableIntraAngleDelta->Location = System::Drawing::Point(10, 40);
            this->fcgLBEnableIntraAngleDelta->Name = L"fcgLBEnableIntraAngleDelta";
            this->fcgLBEnableIntraAngleDelta->Size = System::Drawing::Size(90, 14);
            this->fcgLBEnableIntraAngleDelta->TabIndex = 155;
            this->fcgLBEnableIntraAngleDelta->Text = L"IntraAngleDelta";
            // 
            // fcgCXHighBitDepthModeDecision
            // 
            this->fcgCXHighBitDepthModeDecision->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXHighBitDepthModeDecision->FormattingEnabled = true;
            this->fcgCXHighBitDepthModeDecision->Location = System::Drawing::Point(167, 377);
            this->fcgCXHighBitDepthModeDecision->Name = L"fcgCXHighBitDepthModeDecision";
            this->fcgCXHighBitDepthModeDecision->Size = System::Drawing::Size(118, 22);
            this->fcgCXHighBitDepthModeDecision->TabIndex = 115;
            this->fcgCXHighBitDepthModeDecision->Tag = L"reCmd";
            // 
            // fcgLBHighBitDepthModeDecision
            // 
            this->fcgLBHighBitDepthModeDecision->AutoSize = true;
            this->fcgLBHighBitDepthModeDecision->Location = System::Drawing::Point(10, 380);
            this->fcgLBHighBitDepthModeDecision->Name = L"fcgLBHighBitDepthModeDecision";
            this->fcgLBHighBitDepthModeDecision->Size = System::Drawing::Size(152, 14);
            this->fcgLBHighBitDepthModeDecision->TabIndex = 153;
            this->fcgLBHighBitDepthModeDecision->Text = L"HighBitDepthModeDecision";
            // 
            // fcgCXEnableFilterIntra
            // 
            this->fcgCXEnableFilterIntra->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableFilterIntra->FormattingEnabled = true;
            this->fcgCXEnableFilterIntra->Location = System::Drawing::Point(167, 167);
            this->fcgCXEnableFilterIntra->Name = L"fcgCXEnableFilterIntra";
            this->fcgCXEnableFilterIntra->Size = System::Drawing::Size(118, 22);
            this->fcgCXEnableFilterIntra->TabIndex = 107;
            this->fcgCXEnableFilterIntra->Tag = L"reCmd";
            // 
            // fcgLBEnableFilterIntra
            // 
            this->fcgLBEnableFilterIntra->AutoSize = true;
            this->fcgLBEnableFilterIntra->Location = System::Drawing::Point(10, 170);
            this->fcgLBEnableFilterIntra->Name = L"fcgLBEnableFilterIntra";
            this->fcgLBEnableFilterIntra->Size = System::Drawing::Size(60, 14);
            this->fcgLBEnableFilterIntra->TabIndex = 151;
            this->fcgLBEnableFilterIntra->Text = L"FilterIntra";
            // 
            // fcgLBAltRefNframes
            // 
            this->fcgLBAltRefNframes->AutoSize = true;
            this->fcgLBAltRefNframes->Location = System::Drawing::Point(330, 66);
            this->fcgLBAltRefNframes->Name = L"fcgLBAltRefNframes";
            this->fcgLBAltRefNframes->Size = System::Drawing::Size(84, 14);
            this->fcgLBAltRefNframes->TabIndex = 143;
            this->fcgLBAltRefNframes->Text = L"AltRefNframes";
            // 
            // fcgNUAltRefNframes
            // 
            this->fcgNUAltRefNframes->Location = System::Drawing::Point(480, 64);
            this->fcgNUAltRefNframes->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->fcgNUAltRefNframes->Name = L"fcgNUAltRefNframes";
            this->fcgNUAltRefNframes->Size = System::Drawing::Size(64, 21);
            this->fcgNUAltRefNframes->TabIndex = 123;
            this->fcgNUAltRefNframes->Tag = L"reCmd";
            this->fcgNUAltRefNframes->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
            // 
            // fcgLBAltRefStrength
            // 
            this->fcgLBAltRefStrength->AutoSize = true;
            this->fcgLBAltRefStrength->Location = System::Drawing::Point(330, 40);
            this->fcgLBAltRefStrength->Name = L"fcgLBAltRefStrength";
            this->fcgLBAltRefStrength->Size = System::Drawing::Size(86, 14);
            this->fcgLBAltRefStrength->TabIndex = 141;
            this->fcgLBAltRefStrength->Text = L"AltRefStrength";
            // 
            // fcgNUAltRefStrength
            // 
            this->fcgNUAltRefStrength->Location = System::Drawing::Point(480, 38);
            this->fcgNUAltRefStrength->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
            this->fcgNUAltRefStrength->Name = L"fcgNUAltRefStrength";
            this->fcgNUAltRefStrength->Size = System::Drawing::Size(64, 21);
            this->fcgNUAltRefStrength->TabIndex = 121;
            this->fcgNUAltRefStrength->Tag = L"reCmd";
            this->fcgNUAltRefStrength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
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
            this->fcgtabPageExSettings->Size = System::Drawing::Size(608, 493);
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
            this->fcggroupBoxExSettings->Controls->Add(this->fcgCBAfs24fpsMode);
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
            // fcgCBAfs24fpsMode
            // 
            this->fcgCBAfs24fpsMode->AutoSize = true;
            this->fcgCBAfs24fpsMode->Location = System::Drawing::Point(34, 77);
            this->fcgCBAfs24fpsMode->Name = L"fcgCBAfs24fpsMode";
            this->fcgCBAfs24fpsMode->Size = System::Drawing::Size(67, 18);
            this->fcgCBAfs24fpsMode->TabIndex = 2;
            this->fcgCBAfs24fpsMode->Tag = L"chValue";
            this->fcgCBAfs24fpsMode->Text = L"24fps化";
            this->fcgCBAfs24fpsMode->UseVisualStyleBackColor = true;
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
            this->fcgCSExeFiles->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(1) { this->fcgTSExeFileshelp });
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
            this->fcgtoolStripSettings->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(15) {
                this->fcgTSBSave,
                    this->fcgTSBSaveNew, this->fcgTSBDelete, this->fcgtoolStripSeparator1, this->fcgTSSettings, this->fcgTSBCMDOnly, this->toolStripSeparator3,
                    this->fcgTSBBitrateCalc, this->toolStripSeparator5, this->fcgTSBUpdate, this->toolStripSeparator2, this->fcgTSBOtherSettings,
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
            this->fcgTSBSave->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBSave.Image")));
            this->fcgTSBSave->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBSave->Name = L"fcgTSBSave";
            this->fcgTSBSave->Size = System::Drawing::Size(86, 22);
            this->fcgTSBSave->Text = L"上書き保存";
            this->fcgTSBSave->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSBSave_Click);
            // 
            // fcgTSBSaveNew
            // 
            this->fcgTSBSaveNew->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBSaveNew.Image")));
            this->fcgTSBSaveNew->ImageTransparentColor = System::Drawing::Color::Black;
            this->fcgTSBSaveNew->Name = L"fcgTSBSaveNew";
            this->fcgTSBSaveNew->Size = System::Drawing::Size(77, 22);
            this->fcgTSBSaveNew->Text = L"新規保存";
            this->fcgTSBSaveNew->Click += gcnew System::EventHandler(this, &frmConfig::fcgTSBSaveNew_Click);
            // 
            // fcgTSBDelete
            // 
            this->fcgTSBDelete->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBDelete.Image")));
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
            this->fcgTSSettings->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSSettings.Image")));
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
            this->fcgTSBCMDOnly->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBCMDOnly.Image")));
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
            // fcgTSBBitrateCalc
            // 
            this->fcgTSBBitrateCalc->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSBBitrateCalc->CheckOnClick = true;
            this->fcgTSBBitrateCalc->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->fcgTSBBitrateCalc->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBBitrateCalc.Image")));
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
            // fcgTSBUpdate
            // 
            this->fcgTSBUpdate->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSBUpdate->CheckOnClick = true;
            this->fcgTSBUpdate->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->fcgTSBUpdate->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBUpdate.Image")));
            this->fcgTSBUpdate->ImageTransparentColor = System::Drawing::Color::Magenta;
            this->fcgTSBUpdate->Name = L"fcgTSBUpdate";
            this->fcgTSBUpdate->Size = System::Drawing::Size(35, 22);
            this->fcgTSBUpdate->Text = L"更新";
            this->fcgTSBUpdate->CheckedChanged += gcnew System::EventHandler(this, &frmConfig::fcgTSBUpdate_CheckedChanged);
            // 
            // toolStripSeparator2
            // 
            this->toolStripSeparator2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->toolStripSeparator2->Name = L"toolStripSeparator2";
            this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
            // 
            // fcgTSBOtherSettings
            // 
            this->fcgTSBOtherSettings->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
            this->fcgTSBOtherSettings->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
            this->fcgTSBOtherSettings->Image = (cli::safe_cast<System::Drawing::Image ^>(resources->GetObject(L"fcgTSBOtherSettings.Image")));
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
            this->fcgTSTSettingsNotes->Size = System::Drawing::Size(200, 25);
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
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageMPG);
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageMux);
            this->fcgtabControlMux->Controls->Add(this->fcgtabPageBat);
            this->fcgtabControlMux->Font = (gcnew System::Drawing::Font(L"Meiryo UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(128)));
            this->fcgtabControlMux->Location = System::Drawing::Point(622, 331);
            this->fcgtabControlMux->Name = L"fcgtabControlMux";
            this->fcgtabControlMux->SelectedIndex = 0;
            this->fcgtabControlMux->Size = System::Drawing::Size(384, 214);
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
            this->fcgtabPageMP4->Padding = System::Windows::Forms::Padding(3);
            this->fcgtabPageMP4->Size = System::Drawing::Size(376, 187);
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
            this->fcgBTTC2MP4Path->Location = System::Drawing::Point(340, 87);
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
            this->fcgTXTC2MP4Path->Location = System::Drawing::Point(136, 88);
            this->fcgTXTC2MP4Path->Name = L"fcgTXTC2MP4Path";
            this->fcgTXTC2MP4Path->Size = System::Drawing::Size(202, 21);
            this->fcgTXTC2MP4Path->TabIndex = 5;
            this->fcgTXTC2MP4Path->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXTC2MP4Path_TextChanged);
            this->fcgTXTC2MP4Path->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXTC2MP4Path->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
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
            this->fcgTXMP4MuxerPath->Location = System::Drawing::Point(136, 66);
            this->fcgTXMP4MuxerPath->Name = L"fcgTXMP4MuxerPath";
            this->fcgTXMP4MuxerPath->Size = System::Drawing::Size(202, 21);
            this->fcgTXMP4MuxerPath->TabIndex = 3;
            this->fcgTXMP4MuxerPath->Tag = L"";
            this->fcgTXMP4MuxerPath->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXMP4MuxerPath_TextChanged);
            this->fcgTXMP4MuxerPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXMP4MuxerPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            // 
            // fcgLBTC2MP4Path
            // 
            this->fcgLBTC2MP4Path->AutoSize = true;
            this->fcgLBTC2MP4Path->Location = System::Drawing::Point(4, 91);
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
            this->fcgtabPageMKV->Padding = System::Windows::Forms::Padding(3);
            this->fcgtabPageMKV->Size = System::Drawing::Size(376, 187);
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
            // fcgtabPageMPG
            // 
            this->fcgtabPageMPG->Controls->Add(this->fcgBTMPGMuxerPath);
            this->fcgtabPageMPG->Controls->Add(this->fcgTXMPGMuxerPath);
            this->fcgtabPageMPG->Controls->Add(this->fcgLBMPGMuxerPath);
            this->fcgtabPageMPG->Controls->Add(this->fcgCXMPGCmdEx);
            this->fcgtabPageMPG->Controls->Add(this->fcgLBMPGMuxerCmdEx);
            this->fcgtabPageMPG->Controls->Add(this->fcgCBMPGMuxerExt);
            this->fcgtabPageMPG->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageMPG->Name = L"fcgtabPageMPG";
            this->fcgtabPageMPG->Size = System::Drawing::Size(376, 187);
            this->fcgtabPageMPG->TabIndex = 4;
            this->fcgtabPageMPG->Text = L"mpg";
            this->fcgtabPageMPG->UseVisualStyleBackColor = true;
            // 
            // fcgBTMPGMuxerPath
            // 
            this->fcgBTMPGMuxerPath->Location = System::Drawing::Point(341, 98);
            this->fcgBTMPGMuxerPath->Name = L"fcgBTMPGMuxerPath";
            this->fcgBTMPGMuxerPath->Size = System::Drawing::Size(30, 23);
            this->fcgBTMPGMuxerPath->TabIndex = 23;
            this->fcgBTMPGMuxerPath->Text = L"...";
            this->fcgBTMPGMuxerPath->UseVisualStyleBackColor = true;
            this->fcgBTMPGMuxerPath->Click += gcnew System::EventHandler(this, &frmConfig::fcgBTMPGMuxerPath_Click);
            // 
            // fcgTXMPGMuxerPath
            // 
            this->fcgTXMPGMuxerPath->Location = System::Drawing::Point(132, 99);
            this->fcgTXMPGMuxerPath->Name = L"fcgTXMPGMuxerPath";
            this->fcgTXMPGMuxerPath->Size = System::Drawing::Size(207, 21);
            this->fcgTXMPGMuxerPath->TabIndex = 22;
            this->fcgTXMPGMuxerPath->TextChanged += gcnew System::EventHandler(this, &frmConfig::fcgTXMPGMuxerPath_TextChanged);
            this->fcgTXMPGMuxerPath->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_DragDrop);
            this->fcgTXMPGMuxerPath->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &frmConfig::fcgSetDragDropFilename_Enter);
            // 
            // fcgLBMPGMuxerPath
            // 
            this->fcgLBMPGMuxerPath->AutoSize = true;
            this->fcgLBMPGMuxerPath->Location = System::Drawing::Point(5, 102);
            this->fcgLBMPGMuxerPath->Name = L"fcgLBMPGMuxerPath";
            this->fcgLBMPGMuxerPath->Size = System::Drawing::Size(49, 14);
            this->fcgLBMPGMuxerPath->TabIndex = 25;
            this->fcgLBMPGMuxerPath->Text = L"～の指定";
            // 
            // fcgCXMPGCmdEx
            // 
            this->fcgCXMPGCmdEx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXMPGCmdEx->FormattingEnabled = true;
            this->fcgCXMPGCmdEx->Location = System::Drawing::Point(214, 65);
            this->fcgCXMPGCmdEx->Name = L"fcgCXMPGCmdEx";
            this->fcgCXMPGCmdEx->Size = System::Drawing::Size(157, 22);
            this->fcgCXMPGCmdEx->TabIndex = 21;
            this->fcgCXMPGCmdEx->Tag = L"chValue";
            // 
            // fcgLBMPGMuxerCmdEx
            // 
            this->fcgLBMPGMuxerCmdEx->AutoSize = true;
            this->fcgLBMPGMuxerCmdEx->Location = System::Drawing::Point(140, 68);
            this->fcgLBMPGMuxerCmdEx->Name = L"fcgLBMPGMuxerCmdEx";
            this->fcgLBMPGMuxerCmdEx->Size = System::Drawing::Size(68, 14);
            this->fcgLBMPGMuxerCmdEx->TabIndex = 24;
            this->fcgLBMPGMuxerCmdEx->Text = L"拡張オプション";
            // 
            // fcgCBMPGMuxerExt
            // 
            this->fcgCBMPGMuxerExt->AutoSize = true;
            this->fcgCBMPGMuxerExt->Location = System::Drawing::Point(11, 67);
            this->fcgCBMPGMuxerExt->Name = L"fcgCBMPGMuxerExt";
            this->fcgCBMPGMuxerExt->Size = System::Drawing::Size(113, 18);
            this->fcgCBMPGMuxerExt->TabIndex = 20;
            this->fcgCBMPGMuxerExt->Tag = L"chValue";
            this->fcgCBMPGMuxerExt->Text = L"外部muxerを使用";
            this->fcgCBMPGMuxerExt->UseVisualStyleBackColor = true;
            // 
            // fcgtabPageMux
            // 
            this->fcgtabPageMux->Controls->Add(this->fcgCXMuxPriority);
            this->fcgtabPageMux->Controls->Add(this->fcgLBMuxPriority);
            this->fcgtabPageMux->Location = System::Drawing::Point(4, 23);
            this->fcgtabPageMux->Name = L"fcgtabPageMux";
            this->fcgtabPageMux->Size = System::Drawing::Size(376, 187);
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
            this->fcgtabPageBat->Size = System::Drawing::Size(376, 187);
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
            this->fcgLBBatAfterPath->Size = System::Drawing::Size(61, 14);
            this->fcgLBBatAfterPath->TabIndex = 9;
            this->fcgLBBatAfterPath->Text = L"バッチファイル";
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
            this->fcgLBBatBeforePath->Size = System::Drawing::Size(61, 14);
            this->fcgLBBatBeforePath->TabIndex = 2;
            this->fcgLBBatBeforePath->Text = L"バッチファイル";
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
            this->fcgTXCmd->Location = System::Drawing::Point(9, 547);
            this->fcgTXCmd->Name = L"fcgTXCmd";
            this->fcgTXCmd->ReadOnly = true;
            this->fcgTXCmd->Size = System::Drawing::Size(992, 21);
            this->fcgTXCmd->TabIndex = 4;
            this->fcgTXCmd->DoubleClick += gcnew System::EventHandler(this, &frmConfig::fcgTXCmd_DoubleClick);
            // 
            // fcgBTCancel
            // 
            this->fcgBTCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->fcgBTCancel->Location = System::Drawing::Point(771, 570);
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
            this->fcgBTOK->Location = System::Drawing::Point(893, 570);
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
            this->fcgBTDefault->Location = System::Drawing::Point(9, 572);
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
            this->fcgLBVersionDate->Location = System::Drawing::Point(416, 579);
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
            this->fcgLBVersion->Location = System::Drawing::Point(180, 579);
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
            this->fcgTTX264->ToolTipTitle = L"x264 options...";
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
            this->fcgTTX264Version->ToolTipTitle = L"x264 バージョン情報...";
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
            this->fcgLBguiExBlog->Location = System::Drawing::Point(623, 579);
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
            this->fcgtabControlAudio->Location = System::Drawing::Point(622, 25);
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
            this->fcgtabPageAudioMain->Padding = System::Windows::Forms::Padding(3);
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
            this->fcgCBAudioEncTiming->Location = System::Drawing::Point(242, 54);
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
            this->fcgtabPageAudioOther->Padding = System::Windows::Forms::Padding(3);
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
            this->fcgLBBatAfterAudioPath->Size = System::Drawing::Size(61, 14);
            this->fcgLBBatAfterAudioPath->TabIndex = 57;
            this->fcgLBBatAfterAudioPath->Text = L"バッチファイル";
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
            this->fcgLBBatBeforeAudioPath->Size = System::Drawing::Size(61, 14);
            this->fcgLBBatBeforeAudioPath->TabIndex = 50;
            this->fcgLBBatBeforeAudioPath->Text = L"バッチファイル";
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
            // fcgCXEnableLocalWarp
            // 
            this->fcgCXEnableLocalWarp->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->fcgCXEnableLocalWarp->FormattingEnabled = true;
            this->fcgCXEnableLocalWarp->Location = System::Drawing::Point(494, 392);
            this->fcgCXEnableLocalWarp->Name = L"fcgCXEnableLocalWarp";
            this->fcgCXEnableLocalWarp->Size = System::Drawing::Size(106, 22);
            this->fcgCXEnableLocalWarp->TabIndex = 91;
            this->fcgCXEnableLocalWarp->Tag = L"reCmd";
            // 
            // fcgLBEnableLocalWarp
            // 
            this->fcgLBEnableLocalWarp->AutoSize = true;
            this->fcgLBEnableLocalWarp->Location = System::Drawing::Point(375, 395);
            this->fcgLBEnableLocalWarp->Name = L"fcgLBEnableLocalWarp";
            this->fcgLBEnableLocalWarp->Size = System::Drawing::Size(113, 14);
            this->fcgLBEnableLocalWarp->TabIndex = 90;
            this->fcgLBEnableLocalWarp->Text = L"LocalWarpedMotion";
            // 
            // fcgLBUseDefaultMeHme
            // 
            this->fcgLBUseDefaultMeHme->AutoSize = true;
            this->fcgLBUseDefaultMeHme->Location = System::Drawing::Point(374, 445);
            this->fcgLBUseDefaultMeHme->Name = L"fcgLBUseDefaultMeHme";
            this->fcgLBUseDefaultMeHme->Size = System::Drawing::Size(116, 14);
            this->fcgLBUseDefaultMeHme->TabIndex = 94;
            this->fcgLBUseDefaultMeHme->Text = L"Use default me hme";
            // 
            // fcgLBEnableGlobalMotion
            // 
            this->fcgLBEnableGlobalMotion->AutoSize = true;
            this->fcgLBEnableGlobalMotion->Location = System::Drawing::Point(375, 421);
            this->fcgLBEnableGlobalMotion->Name = L"fcgLBEnableGlobalMotion";
            this->fcgLBEnableGlobalMotion->Size = System::Drawing::Size(78, 14);
            this->fcgLBEnableGlobalMotion->TabIndex = 92;
            this->fcgLBEnableGlobalMotion->Text = L"GlobalMotion";
            // 
            // fcgLBEnableStatReport
            // 
            this->fcgLBEnableStatReport->AutoSize = true;
            this->fcgLBEnableStatReport->Location = System::Drawing::Point(375, 469);
            this->fcgLBEnableStatReport->Name = L"fcgLBEnableStatReport";
            this->fcgLBEnableStatReport->Size = System::Drawing::Size(69, 14);
            this->fcgLBEnableStatReport->TabIndex = 96;
            this->fcgLBEnableStatReport->Text = L"Stat Report";
            // 
            // frmConfig
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
            this->ClientSize = System::Drawing::Size(1008, 601);
            this->Controls->Add(this->fcgtabControlAudio);
            this->Controls->Add(this->fcgLBguiExBlog);
            this->Controls->Add(this->fcgLBVersion);
            this->Controls->Add(this->fcgLBVersionDate);
            this->Controls->Add(this->fcgBTDefault);
            this->Controls->Add(this->fcgBTOK);
            this->Controls->Add(this->fcgBTCancel);
            this->Controls->Add(this->fcgTXCmd);
            this->Controls->Add(this->fcgtabControlMux);
            this->Controls->Add(this->fcgtoolStripSettings);
            this->Controls->Add(this->fcgtabControlVideo);
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
            this->fcgPNX264Mode->ResumeLayout(false);
            this->fcgPNX264Mode->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUBitrate))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUQP))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUCDEFLevel))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUVBVBufSize))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMaxQP))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMinQP))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUSQW))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUSearchH))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUSearchW))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUTileColumns))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUTileRows))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUIntraRefreshType))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUKeyint))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNULookaheadDistance))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUThreads))->EndInit();
            this->fcgtabPageSVTAV1_2->ResumeLayout(false);
            this->fcgtabPageSVTAV1_2->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUBiasPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUOverShootPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUUnderShootPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMaxSectionPct))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUMinSectionPct))->EndInit();
            this->fcggroupBoxColorMatrix->ResumeLayout(false);
            this->fcggroupBoxColorMatrix->PerformLayout();
            this->fcggroupBoxAepectRatio->ResumeLayout(false);
            this->fcggroupBoxAepectRatio->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAspectRatioY))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAspectRatioX))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAltRefNframes))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAltRefStrength))->EndInit();
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
            this->fcgtabPageMPG->ResumeLayout(false);
            this->fcgtabPageMPG->PerformLayout();
            this->fcgtabPageMux->ResumeLayout(false);
            this->fcgtabPageMux->PerformLayout();
            this->fcgtabPageBat->ResumeLayout(false);
            this->fcgtabPageBat->PerformLayout();
            this->fcgtabControlAudio->ResumeLayout(false);
            this->fcgtabPageAudioMain->ResumeLayout(false);
            this->fcgtabPageAudioMain->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(this->fcgNUAudioBitrate))->EndInit();
            this->fcgtabPageAudioOther->ResumeLayout(false);
            this->fcgtabPageAudioOther->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        const SYSTEM_DATA *sys_dat;
        CONF_GUIEX *conf;
        LocalSettings LocalStg;
        TBValueBitrateConvert TBBConvert;
        System::Threading::Timer^ qualityTimer;
        int timerChangeValue;
        bool CurrentPipeEnabled;
        bool stgChanged;
        String^ CurrentStgDir;
        ToolStripMenuItem^ CheckedStgMenuItem;
        CONF_GUIEX *cnf_stgSelected;
        String^ lastQualityStr;
#if ENABLE_AUOSETUP
        frmUpdate^ frmExeUpdate;
#endif
    private:
        System::Int32 GetCurrentAudioDefaultBitrate();
        delegate System::Void qualityTimerChangeDelegate();
        System::Void InitComboBox();
        System::Void setAudioDisplay();
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
        System::Void GetfcgTSLSettingsNotes(char *notes, int nSize);
        System::Void SetfcgTSLSettingsNotes(const char *notes);
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
        System::Void SetHelpToolTips();
        //System::Void SetHelpToolTipsColorMatrix(Control^ control, const char *type);
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
        System::Void initUpdater();
        System::Void fcgTSBUpdate_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
        System::Void fcgTSBUpdate_UpdateFinished(String^ mes);
        System::Void fcgTSBUpdate_CheckFinished(String^ mes);
        System::Void fcgCXRC_SelectedIndexChanged(System::Object ^sender, System::EventArgs ^e);
    public:
        System::Void InitData(CONF_GUIEX *set_config, const SYSTEM_DATA *system_data);
        System::Void SetVideoBitrate(int bitrate);
        System::Void SetAudioBitrate(int bitrate);
        System::Void InformfbcClosed();
        System::Void InformfruClosed();
    private:
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
            CX->Items->Clear();
            for (int i = 0; list[i].desc; i++)
                CX->Items->Add(String(list[i].desc).ToString());
            CX->EndUpdate();
        }
    private:
        System::Void setComboBox(ComboBox ^CX, const CX_DESC *list) {
            CX->BeginUpdate();
            CX->Items->Clear();
            for (int i = 0; list[i].desc; i++)
                CX->Items->Add(String(list[i].desc).ToString());
            CX->EndUpdate();
        }
    private:
        System::Void setComboBox(ComboBox^ CX, const char * const * list) {
            CX->BeginUpdate();
            CX->Items->Clear();
            for (int i = 0; list[i]; i++)
                CX->Items->Add(String(list[i]).ToString());
            CX->EndUpdate();
        }
    private:
        System::Void setComboBox(ComboBox^ CX, const WCHAR * const * list) {
            CX->BeginUpdate();
            CX->Items->Clear();
            for (int i = 0; list[i]; i++)
                CX->Items->Add(String(list[i]).ToString());
            CX->EndUpdate();
        }
    private:
        System::Void setPriorityList(ComboBox^ CX) {
            CX->BeginUpdate();
            CX->Items->Clear();
            for (int i = 0; priority_table[i].text; i++)
                CX->Items->Add(String(priority_table[i].text).ToString());
            CX->EndUpdate();
        }
    private:
        System::Void setMuxerCmdExNames(ComboBox^ CX, int muxer_index) {
            CX->BeginUpdate();
            CX->Items->Clear();
            MUXER_SETTINGS *mstg = &sys_dat->exstg->s_mux[muxer_index];
            for (int i = 0; i < mstg->ex_count; i++)
                CX->Items->Add(String(mstg->ex_cmd[i].name).ToString());
            CX->EndUpdate();
        }
    private:
        System::Void setAudioEncoderNames() {
            fcgCXAudioEncoder->BeginUpdate();
            fcgCXAudioEncoder->Items->Clear();
            //fcgCXAudioEncoder->Items->AddRange(reinterpret_cast<array<String^>^>(LocalStg.audEncName->ToArray(String::typeid)));
            fcgCXAudioEncoder->Items->AddRange(LocalStg.audEncName->ToArray());
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
                MessageBox::Show(this, L"入力された文字数が多すぎます。減らしてください。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
        System::Void fcgTXX264Path_Leave(System::Object^  sender, System::EventArgs^  e) {
            SetX264VersionToolTip(fcgTXX264Path->Text);
        }
    private:
        System::Void fcgTXX264PathSub_Leave(System::Object^  sender, System::EventArgs^  e) {
            SetX264VersionToolTip(fcgTXX264PathSub->Text);
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
        System::Void fcgBTMPGMuxerPath_Click(System::Object^  sender, System::EventArgs^  e) {
            openExeFile(fcgTXMPGMuxerPath, LocalStg.MPGMuxerExeName);
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
            openAndSetFilePath(fcgTXStatusFile, L"ステータスファイル");
        }
    private:
        System::Void fcgBTBatBeforePath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatBeforePath, L"バッチファイル", ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatBeforePath->Text);
        }
    private:
        System::Void fcgBTBatAfterPath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatAfterPath, L"バッチファイル", ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatAfterPath->Text);
        }
    private:
        System::Void fcgBTBatBeforeAudioPath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatBeforeAudioPath, L"バッチファイル", ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatBeforeAudioPath->Text);
        }
    private:
        System::Void fcgBTBatAfterAudioPath_Click(System::Object^  sender, System::EventArgs^  e) {
            if (openAndSetFilePath(fcgTXBatAfterAudioPath, L"バッチファイル", ".bat", LocalStg.LastBatDir))
                LocalStg.LastBatDir = Path::GetDirectoryName(fcgTXBatAfterAudioPath->Text);
        }
    private:
        System::Void SetCXIndex(ComboBox^ CX, int index) {
            CX->SelectedIndex = clamp(index, 0, CX->Items->Count - 1);
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
            init_CONF_GUIEX(&cnf);
            FrmToConf(&cnf);
            char cmdex[2048] = { 0 };
            GetCHARfromString(cmdex, sizeof(cmdex), fcgTXCmdEx->Text);
            CONF_ENCODER enc = get_default_prm();
            set_cmd(&enc, cnf.enc.cmd, true);
            set_cmd(&enc, cmdex, true);
            auto cmd_read = gen_cmd(&enc, false);
            strcpy_s(cnf.enc.cmd, cmd_read.c_str());
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
            init_CONF_GUIEX(conf);
            FrmToConf(conf);
            SaveLocalStg();
            ZeroMemory(conf->oth.notes, sizeof(conf->oth.notes));
            this->Close();
        }
    private:
        System::Void fcgBTCancel_Click(System::Object^  sender, System::EventArgs^  e) {
            this->Close();
        }
    private:
        System::Void fcgBTDefault_Click(System::Object^  sender, System::EventArgs^  e) {
            CONF_GUIEX confDefault;
            init_CONF_GUIEX(&confDefault);
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
            init_CONF_GUIEX(&rebuild);
            fcgTXCmd->Text = FrmToConf(&rebuild);
            if (CheckedStgMenuItem != nullptr)
                ChangePresetNameDisplay(memcmp(&rebuild, cnf_stgSelected, sizeof(CONF_GUIEX)) != 0);
        }
    private:
        System::Void CheckOtherChanges(System::Object^  sender, System::EventArgs^  e) {
            if (CheckedStgMenuItem == nullptr)
                return;
            CONF_GUIEX check_change;
            init_CONF_GUIEX(&check_change);
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
            int c = fcgTXX264Path->SelectionStart;
            LocalStg.x264Path      = fcgTXX264Path->Text;
            fcgTXX264PathSub->Text = LocalStg.x264Path;
            fcgTXX264PathSub->SelectionStart = fcgTXX264PathSub->Text->Length;
            fcgTXX264Path->SelectionStart = c;
            fcgBTX264Path->ContextMenuStrip = (File::Exists(fcgTXX264Path->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXX264PathSub_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.x264Path   = fcgTXX264PathSub->Text;
            int c = fcgTXX264PathSub->SelectionStart;
            fcgTXX264Path->Text = LocalStg.x264Path;
            fcgTXX264Path->SelectionStart = fcgTXX264Path->Text->Length;
            fcgTXX264PathSub->SelectionStart = c;
            fcgBTX264PathSub->ContextMenuStrip = (File::Exists(fcgTXX264PathSub->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXAudioEncoderPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.audEncPath[fcgCXAudioEncoder->SelectedIndex] = fcgTXAudioEncoderPath->Text;
            fcgBTAudioEncoderPath->ContextMenuStrip = (File::Exists(fcgTXAudioEncoderPath->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXMP4MuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.MP4MuxerPath = fcgTXMP4MuxerPath->Text;
            fcgBTMP4MuxerPath->ContextMenuStrip = (File::Exists(fcgTXMP4MuxerPath->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXTC2MP4Path_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.TC2MP4Path = fcgTXTC2MP4Path->Text;
            fcgBTTC2MP4Path->ContextMenuStrip = (File::Exists(fcgTXTC2MP4Path->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXMP4RawMuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.MP4RawPath = fcgTXMP4RawPath->Text;
            fcgBTMP4RawPath->ContextMenuStrip = (File::Exists(fcgTXMP4RawPath->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXMKVMuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.MKVMuxerPath = fcgTXMKVMuxerPath->Text;
            fcgBTMKVMuxerPath->ContextMenuStrip = (File::Exists(fcgTXMKVMuxerPath->Text)) ? fcgCSExeFiles : nullptr;
        }
    private:
        System::Void fcgTXMPGMuxerPath_TextChanged(System::Object^  sender, System::EventArgs^  e) {
            LocalStg.MPGMuxerPath = fcgTXMPGMuxerPath->Text;
            fcgBTMPGMuxerPath->ContextMenuStrip = (File::Exists(fcgTXMPGMuxerPath->Text)) ? fcgCSExeFiles : nullptr;
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
                { fcgBTAudioEncoderPath->Name,   fcgTXAudioEncoderPath->Text,   sys_dat->exstg->s_aud[fcgCXAudioEncoder->SelectedIndex].cmd_help },
                { fcgBTMP4MuxerPath->Name,       fcgTXMP4MuxerPath->Text,       sys_dat->exstg->s_mux[MUXER_MP4].help_cmd },
                { fcgBTTC2MP4Path->Name,         fcgTXTC2MP4Path->Text,         sys_dat->exstg->s_mux[MUXER_TC2MP4].help_cmd },
                { fcgBTMP4RawPath->Name,         fcgTXMP4RawPath->Text,         sys_dat->exstg->s_mux[MUXER_MP4_RAW].help_cmd },
                { fcgBTMKVMuxerPath->Name,       fcgTXMKVMuxerPath->Text,       sys_dat->exstg->s_mux[MUXER_MKV].help_cmd },
                { fcgBTMPGMuxerPath->Name,       fcgTXMPGMuxerPath->Text,       sys_dat->exstg->s_mux[MUXER_MPG].help_cmd }
            };
            for (int i = 0; i < ControlList->Length; i++) {
                if (NULL == String::Compare(CS->SourceControl->Name, ControlList[i].Name)) {
                    ShowExehelp(ControlList[i].Path, String(ControlList[i].args).ToString());
                    return;
                }
            }
            MessageBox::Show(L"ヘルプ表示用のコマンドが設定されていません。", L"エラー", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
