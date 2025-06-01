#include "main.h"
#include <ckButton.h>
#include <ckCheckbox.h>
#include <ckLabel.h>
#include <ckMenu.h>
#include <ckRadiobox.h>
#include <ckTextField.h>
#include <ckTimer.h>
#include <ckWindow.h>
#include <functional>
#include <map>
#include <string.h>

CKTest* app;

int main() {

	// Create a new app.
	app = CKNew CKTest();
	// app->showAlert();

	CKMenuBar* menuBar = CKNew CKMenuBar();

	CKMenuBarItem* menuFile = CKNew CKMenuBarItem("File");
	menuBar->AddMenuItem(menuFile);

	CKMenuItem* meowItem = CKNew CKMenuItem("Meow", 'M', [&meowItem](CKEvent e) {
		app->CKNewMsgBoxError("Hello world!", "This is meow!", "Oh ok", "Bark!");

		meowItem->SetText("Bark");
		meowItem->enabled = false;
	});
	menuFile->AddItem(meowItem);

	CKMenuItem* quitItem = CKNew CKMenuItem("Quit", 'Q', [&quitItem](CKEvent e) {
		app->CKQuit();
	});
	menuFile->AddItem(quitItem);

	CKMenuBarItem* menuTests = CKNew CKMenuBarItem("Tests");
	menuBar->AddMenuItem(menuTests);

	std::map<std::string, std::function<void()>> tests;

	/*** ---------------------------------------------------------------------- */
	/*** Show a simple dialog box
	/-------------------------------------------------------------------------- */

	tests["Message box"] = []() {
		app->CKNewMsgBoxNote("Hello world", "If you are seeing this, then compile was fine!", "OK", "Quit", [](int button) {
			CKLog("Got button index: %d", button);
			if (button == 0) {
				app->CKQuit();
			}
		});
	};

	tests["Message box (No Title)"] = []() {
		app->CKNewMsgBoxNote(nullptr, "If you are seeing this, then compile was fine!", "OK", "Quit", [](int button) {
			CKLog("Got button index: %d", button);
			if (button == 0) {
				app->CKQuit();
			}
		});
	};

	/*** ---------------------------------------------------------------------- */
	/*** Show labels being changed by timers
	/-------------------------------------------------------------------------- */

	tests["Timer"] = []() {
		CKWindow* window = app->CKNewWindow(CKWindowInitParams(CKSize(300, 70)));
		window->SetTitle("Timer");

		CKLabel* label1 = CKNew CKLabel(CKRect(10, 10, 300 - 20, 20));
		label1->SetText("Timer 1 hasn't fired yet..");
		window->AddControl(label1);

		CKLabel* label2 = CKNew CKLabel(CKRect(10, 30, 300 - 20, 20));
		label2->SetText("Timer 2 hasn't fired yet..");
		window->AddControl(label2);

		window->Center();
		window->Show();

		CKTimer* timer = CKNew CKTimer();
		timer->interval = 1000;
		timer->multiRun = true;
		int idx = 0;
		timer->callback = [label1, idx](void* params) mutable {
			char t[256];
			sprintf(t, "Hi! %d (1000ms)", idx);
			idx++;
			label1->SetText(t);
		};
		app->CKAddTimer(timer, window);

		CKTimer* timer2 = CKNew CKTimer();
		timer2->interval = 100;
		timer2->multiRun = true;
		int idx2 = 0;
		timer2->callback = [label2, idx2](void* params) mutable {
			char t[256];
			sprintf(t, "Hi! %d (100ms)", idx2);
			idx2++;
			label2->SetText(t);
		};
		app->CKAddTimer(timer2, window);
	};

	/*** ---------------------------------------------------------------------- */
	/*** Showcase label properties
	/-------------------------------------------------------------------------- */

	tests["Labels"] = []() {
		CKWindow* window = app->CKNewWindow(CKWindowInitParams(CKSize(300, 10)));
		window->SetTitle("Labels");
		int padding = 10;
		for (int i = 0; i < 10; i++) {
			CKLabel* label = CKNew CKLabel(CKSize(300 - (padding * 2), 20));
			label->rect->origin->x = padding;
			label->rect->origin->y = padding + (i * (20 + padding));
			window->AddControl(label);
			window->rect->size->height += label->rect->size->height + padding;

			switch (i) {
				case 0:
					label->SetText("A bold label!");
					label->bold = true;
					break;
				case 1:
					label->SetText("An italic label!");
					label->italic = true;
					break;
				case 2:
					label->SetText("An underlined label!");
					label->underline = true;
					break;
				case 3:
					label->SetText("A bold + underline label!");
					label->bold = true;
					label->underline = true;
					break;
				case 4:
					label->SetText("A centered label!");
					label->justification = CKTextJustification::Center;
					break;
				case 5:
					label->SetText("A red label!");
					label->color = CKColor({255, 0, 0});
					break;
				case 6:
					label->SetText("Geneva at 12 pt");
					label->SetFont(app->CKFontToId("Geneva"));
					label->fontSize = 12;
					break;
				case 7:
					label->SetText("Geneva at 10 pt");
					label->SetFont(app->CKFontToId("Geneva"));
					label->fontSize = 10;
					break;
				case 8:
					label->SetText("Geneva at 8 pt");
					label->SetFont(app->CKFontToId("Geneva"));
					label->fontSize = 8;
					break;
				case 9:
					label->SetText("Geneva at 20 pt");
					label->SetFont(app->CKFontToId("Geneva"));
					label->fontSize = 20;
					break;
				default:
					break;
			}
		}
		window->Center();
		window->Show();
	};

	/*** ---------------------------------------------------------------------- */
	/*** Showcase button properties
	/-------------------------------------------------------------------------- */

	tests["Buttons"] = []() {
		CKWindow* window = app->CKNewWindow(CKWindowInitParams(CKSize(300, 10)));
		window->SetTitle("Buttons");
		int padding = 10;
		for (int i = 0; i < 2; i++) {
			CKButton* button = CKNew CKButton(CKSize(300 - (padding * 2), kCKButtonHeight));
			button->rect->origin->x = padding;
			button->rect->origin->y = padding + (i * (kCKButtonHeight + padding));
			window->AddControl(button);
			window->rect->size->height += button->rect->size->height + padding;

			switch (i) {
				case 0:
					button->SetText("A regular button!");
					break;
				case 1:
					button->SetText("A disabled button!");
					button->enabled = false;
					break;
			}
		}
		window->Center();
		window->Show();
	};

	/*** ---------------------------------------------------------------------- */
	/*** Showcase button properties
	/-------------------------------------------------------------------------- */

	tests["Checkbox and Radios"] = []() {
		CKWindow* window = app->CKNewWindow(CKWindowInitParams(CKSize(300, 10)));
		window->SetTitle("Checkbox and Radios");
		int padding = 10;
		int startY = 0;
		for (int i = 0; i < 2; i++) {
			CKCheckbox* obj = CKNew CKCheckbox(CKSize(300 - (padding * 2), kCKCheckboxHeight));
			obj->rect->origin->x = padding;
			obj->rect->origin->y = padding + startY;
			window->AddControl(obj);
			window->rect->size->height += obj->rect->size->height + padding;

			switch (i) {
				case 0:
					obj->SetText("A regular checkbox!");
					break;
				case 1:
					obj->SetText("A disabled checkbox!");
					obj->enabled = false;
					break;
			}
			startY += obj->rect->size->height + padding;
		}
		for (int i = 0; i < 4; i++) {
			CKRadiobox* obj = CKNew CKRadiobox(CKSize(300 - (padding * 2), kCKRadioboxHeight));
			obj->rect->origin->x = padding;
			obj->rect->origin->y = padding + startY;
			window->AddControl(obj);
			window->rect->size->height += obj->rect->size->height + padding;

			switch (i) {
				case 0:
					obj->SetText("A regular radiobox! (ungrouped)");
					break;
				case 1:
					obj->SetText("A disabled radiobox! (ungrouped)");
					obj->enabled = false;
					break;
				case 2:
					obj->SetText("Grouped Item A");
					obj->groupID = 1;
					obj->SetValue(true);
					break;
				case 3:
					obj->SetText("Grouped Item B");
					obj->groupID = 1;
					obj->SetValue(false);
					break;
			}
			startY += obj->rect->size->height + padding;
		}
		window->Center();
		window->Show();
	};

	/*** ---------------------------------------------------------------------- */
	/*** Showcase button properties
	/-------------------------------------------------------------------------- */

	tests["Textfield"] = []() {
		CKWindow* window = app->CKNewWindow(CKWindowInitParams(CKSize(300, 10)));
		window->SetTitle("Textfield");
		int padding = 10;
		for (int i = 0; i < 2; i++) {
			CKTextField* button = CKNew CKTextField(CKSize(300 - (padding * 2), kCKTextFieldHeight));
			button->rect->origin->x = padding;
			button->rect->origin->y = padding + (i * (kCKTextFieldHeight + padding));
			window->AddControl(button);
			window->rect->size->height += button->rect->size->height + padding;

			switch (i) {
				case 0:
					button->SetText("A regular textfield!");
					break;
				case 1:
					button->SetText("A disabled textfield!");
					button->enabled = false;
					break;
			}
		}
		window->Center();
		window->Show();
	};

	for (const auto& [name, test] : tests) {
		CKMenuItem* item = CKNew CKMenuItem(name.c_str(), 0, [&item, test](CKEvent e) {
			test();
		});
		menuTests->AddItem(item);
	}

	app->CKSetMenu(menuBar);

	// Run loop: without this, your app will quit as soon as it launches.
	while (!app->CKLoop(5)) {
		;
	}

	delete app;
	return 0;
}