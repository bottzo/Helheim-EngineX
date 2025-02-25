#ifndef _EDITOR_CONTROL_PANEL_H_
#define _EDITOR_CONTROL_PANEL_H_
#include "Panel.h"
#define EDITORCONTROLPANEL "Editor Controls##"

#include "imgui.h"
#include "ImGuizmo.h"
#include "Math/float3.h"


enum class GameState {
	PLAY,
	PAUSE,
	PLAY_PAUSE,
	STOP
};

class EditorControlPanel : public Panel
{
public:
	EditorControlPanel();
	~EditorControlPanel();

	void Draw(int windowFlags) override;

	const ImGuizmo::OPERATION GetGuizmoOperation() { return mCurrentGuizmoOperation;}
	const ImGuizmo::MODE GetGuizmoMode() { return mCurrentGuizmoMode; }
	const bool GetUseSnap() { return mUseSnap; }
	const float3 GetSnap() { return mSnap; }

	void Play();
	void Pause();
	void Stop();
	void Step();

private:
	ImGuizmo::OPERATION mCurrentGuizmoOperation = ImGuizmo::TRANSLATE;
	ImGuizmo::MODE mCurrentGuizmoMode = ImGuizmo::LOCAL;
	bool mUseSnap = false;
	float3 mSnap = { 1.f, 1.f, 1.f };
	GameState mState = GameState::STOP;

};
#endif /* _EDITOR_CONTROL_PANEL_H_ */