#pragma once

#include <functional>
#include "DirectInputPadState.h"

class FDirectInputJoystick;

struct AnalogDelegate
{
	std::function<float()>	Axis_;

	// Axis�Ƀ{�^�����ݒ肳��Ă����ꍇ�A
	// ���̕������`�F�b�N����̂Ɏg��
	std::function<float()>	AxisNegative_;

	FDIKeyMapInfo DIKeyAxis_;
	FDIKeyMapInfo DIKeyAxisNegative_;
};

struct BtnDelegate
{
	std::function<bool()>	IsPress_;
	std::function<bool()>	IsPush_;
	std::function<bool()>	IsRelease_;

	FDIKeyMapInfo DIKey_;
};

//! DirectInputPad��XInput�Ƃ��ăG�~�����[�V��������N���X
class FXInputJoystickEmu
{
public:
	void Init(TSharedRef<FDirectInputJoystick> DIPad);

	//! ��Ԃɍ��킹��Event�𔭐�������
	void Event(const TSharedPtr<FGenericApplicationMessageHandler>& MessageHandler);

private:
	void EventAnalog(FName XIName, const AnalogDelegate& Delegate, const TSharedPtr<FGenericApplicationMessageHandler>& MessageHandler);
	void EventButton(FName XIName, const BtnDelegate& Delegate, const TSharedPtr<FGenericApplicationMessageHandler>& MessageHandler);

public:
	//! �L�[�}�b�v��ݒ肷��
	void SetKeyMap(EXInputPadKeyNames eXIKey, FDIKeyMapInfo DIKeyInfo);

private:
	//! �A�i���O�}�b�v��ݒ肷��BeDIKey���{�^���̏ꍇ�AbNegative�ɏ]�����ꏊ�ɐݒ肳���
	//! eXIKey���{�^���̏ꍇ�́A����������Ȃ�
	void SetAnalogMap(EXInputPadKeyNames eXIKey, FDIKeyMapInfo DIKeyInfo);
	//! �{�^���}�b�v��ݒ肷��BeDIKey�����̏ꍇ�AbNegative�ɏ]���������̒l���g����
	//! eXIKey���A�i���O�̏ꍇ�A�A�i���O�̃{�^�����암���ɐݒ肳���
	void SetButtonMap(EXInputPadKeyNames eXIKey, FDIKeyMapInfo DIKeyInfo);

public:
	TArray<FDIKeyMapInfo> GetKeyMap(EXInputPadKeyNames eXIKey);

private:
	//! eXIKey�Ƃ��Đݒ肳��Ă���L�[�}�b�v�������o��
	TArray<FDIKeyMapInfo>	GetAnalogDIKeyMapInfo(EXInputPadKeyNames eXIKey)const;
	FDIKeyMapInfo			GetButtonDIKeyMapInfo(EXInputPadKeyNames eXIKey)const;

public:
	TSharedPtr<FDirectInputJoystick> GetDIPad()const{ return DIPad_; }

private:
	void SetAnalogMapAnalog(EDirectInputPadKeyNames eDIKey, AnalogDelegate& Analog, BtnDelegate& Pos, BtnDelegate& Neg);
	void SetAnalogMapBtn(EDirectInputPadKeyNames eDIKey, AnalogDelegate& Analog, BtnDelegate& Btn, bool bNegative=false);

	// bNegative��true�̎��A�{�^�����g����delegate�����̒l��Ԃ��悤�ɂȂ�
	std::function<float()>			CreateAnalogDelegate(EDirectInputPadKeyNames eDIKey, bool bNegative=false);
	// 0:Press 1:Push 2:Release�@bNegative��true�̎��A�����g����delegate�͕��̕������g���Ĕ��肷��
	TArray<std::function<bool()>>	CreateButtonDelegate(EDirectInputPadKeyNames eDIKey, bool bNegative=false);

private:
	// �Ή�����DirectInputPad
	TSharedPtr<FDirectInputJoystick> DIPad_;

	// �f���Q�[�g�Q
	AnalogDelegate	LeftAnalogX_;
	AnalogDelegate	LeftAnalogY_;
	AnalogDelegate	RightAnalogX_;
	AnalogDelegate	RightAnalogY_;
	AnalogDelegate	LeftTriggerAnalog_;  // 0.0~1.0
	AnalogDelegate	RightTriggerAnalog_; // 0.0~1.0

	BtnDelegate		LeftStickUp_;
	BtnDelegate		LeftStickDown_;
	BtnDelegate		LeftStickRight_;
	BtnDelegate		LeftStickLeft_;

	BtnDelegate		RightStickUp_;
	BtnDelegate		RightStickDown_;
	BtnDelegate		RightStickRight_;
	BtnDelegate		RightStickLeft_;

	BtnDelegate		BtnA_;
	BtnDelegate		BtnB_;
	BtnDelegate		BtnX_;
	BtnDelegate		BtnY_;

	BtnDelegate		BtnLB_;
	BtnDelegate		BtnRB_;
	BtnDelegate		LeftTrigger_;
	BtnDelegate		RightTrigger_;

	BtnDelegate		BtnBack_;
	BtnDelegate		BtnStart_;

	BtnDelegate		BtnLStick_;
	BtnDelegate		BtnRStick_;

	BtnDelegate		DPadUp_;
	BtnDelegate		DPadDown_;
	BtnDelegate		DPadRight_;
	BtnDelegate		DPadLeft_;
};
