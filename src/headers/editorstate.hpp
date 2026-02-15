#pragma once

class EditorUi;
class LevelEditorLayer;

struct editorstate {
	EditorUI* editorUI = nullptr;
	LevelEditorLayer* levelEditorLayer = nullptr;
	matjson::Value parameters;
	bool initialized = false;

	void reset() {
		editorUI = nullptr;
		levelEditorLayer = nullptr;
		initialized = false;
	};

};

editorstate& getEditorState();
