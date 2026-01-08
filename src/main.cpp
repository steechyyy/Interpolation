/**
 * Include the Geode headers.
 */

#include <common.hpp>
/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */




class $modify(TheEditorPauseLayer, EditorPauseLayer) {
	
	struct Fields {
		EditorUI* editorUi = nullptr;
		std::ostringstream objDesc;
		std::string objString;
		matjson::Value parameters;
	};
	
	bool init(LevelEditorLayer * layer) {

		if (!EditorPauseLayer::init(layer)) {
			return false;
		}

		if (!Mod::get()->setSavedValue<bool>("shown-tut-notice", true)) {
			FLAlertLayer::create(
				"interpolation mod tutorial",
				"if you're unsure on how to utilize this mod, don't hesitate to look for a tutorial",
				"go away"
			)->show();
		}

		std::filesystem::path parametersJsonPath = Mod::get()->getResourcesDir() / "parameters.json";
		std::ifstream file(parametersJsonPath);
		if (!file.is_open()) {
			log::error("failed to open json");
			return true;
		}
		auto result = matjson::parse(file);
		if (!result) {
			log::error("failed to parse json, {}", result.unwrapErr());
			return true;
		}
		m_fields->parameters = result.unwrap();

		auto btnSprite = ButtonSprite::create(
			"Interpolate", 30, 0, .4f, true, "bigFont.fnt", "GJ_button_04.png", 30.f
		);

		auto theButton = CCMenuItemSpriteExtra::create(
			btnSprite,
			this,
			menu_selector(TheEditorPauseLayer::onClicked)
		);

		auto menu = this->getChildByID("top-menu");
		menu->addChild(theButton);

		menu->updateLayout();

		return true;
	};

	void onClicked(CCObject*) {
		// log::debug("mandatory string, {}", m_fields->parameters["901"]["name"].asString().unwrap());
		// HELP I CANT BELIEVE I FIGURED OUT HOW TO LOAD FUCKASS JSONS IN ONE NIGHT OMG
		// im so happy rn i could do da jordan [4:45AM 2025.12.29]

		auto editorLayer = this->m_editorLayer;
		auto editorUi = editorLayer->m_editorUI;
	
		CCArray* objs = editorUi->getSelectedObjects();

		if (objs->count() != 2) {
			FLAlertLayer::create("Interpolate", "BRUH SELECT TWO OBJECTs", "bruh")->show();
			return;
		}
		auto obj01 = static_cast<GameObject*>(objs->objectAtIndex(0));
		auto obj02 = static_cast<GameObject*>(objs->objectAtIndex(1));

		//log::debug("{}", obj01->m_objectID);
		if (obj01->m_objectID != obj02->m_objectID) {
			FLAlertLayer::create("Interpolate", "BRUH SELECT TWO OBJECTS OF THE SAME KIND", "bruh")->show();
			return;
		};

		// log::debug("hi: {}", m_fields->parameters[std::to_string(obj01->m_objectID)]["name"].asString().unwrap());
		m_fields->objDesc << "1," << obj01->m_objectID << ",2," << obj01->m_positionX << ",3," << obj01->m_positionY << ";";

		m_fields->objString = m_fields->objDesc.str();
		m_fields->objString.pop_back(); //pop back

		editorLayer->createObjectsFromString(m_fields->objString.c_str(), true, true);
		//FLAlertLayer::create("Success", "successfully interpolated" , "OK")->show();
		

		Point newPoint(0.5f, 0.7f);
		if (Spline* wow = SplineManager::get().newSpline("ultimate spline")) {
			wow->addPoint(std::move(newPoint));
			InterpolationMenu::create(wow)->show();

		}
		else {
			FLAlertLayer::create(
				"oh no!",
				"something went wrong..",
				"ok sorry.."
			)->show();
		};

		std::vector<std::string> res;
		for (const auto& ptr : SplineManager::get().getSplines()) {
			res.push_back(ptr->getId());

			log::debug("{}", res);
		};
	};
	
};

class $modify(TheEditorUI, EditorUI) {

	/*
	struct Fields {
		EditorPauseLayer* epl;
	};

	bool init(LevelEditorLayer * editorLayer) {
		if (!EditorUI::init(editorLayer)) {
			return false;
		}

		auto caster = static_cast<TheEditorPauseLayer*>(m_fields->epl);
		caster->initEditorUi();

	}
	*/

};

class $modify(TheLevelEditorLayer, LevelEditorLayer) {

	/*
	bool init(GJGameLevel* level, bool noUi) {
		if (!LevelEditorLayer::init(level, noUi)) {
			return false;
		}

		return true;
	}
	*/

};

class $modify(MyMenuLayer, MenuLayer) {
	
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/

	bool init() {

		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */

		if (!MenuLayer::init()) {
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		*/

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		*/

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			/**
			 * Here we use the name we set earlier for our modify class.
			*/
			menu_selector(MyMenuLayer::onMyButton)
		);

		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		*/

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		*/

		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		*/

		menu->updateLayout();

		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */

		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/

	void onMyButton(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
	}
};