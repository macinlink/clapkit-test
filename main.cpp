#include <ckApp.h>

class CKTest: public CKApp {
    public:
        CKTest() { }
        ~CKTest() { }
};

CKTest* app;

void showAlert() {
    app->CKNewAlert("Hello world", "If you are seeing this, then compile was fine!", "Again!", "Quit", [](int button) {
        CKLog("button: %d", button);
        if (button == 0) {
            app->Quit();
        } else {
            showAlert();
        }
    });
}

int main() {
    
    // Create a new app.
    app = CKNew CKTest();

    // Show an alert!
    showAlert();

    // Run loop: without this, your app will quit as soon as it launches.
    while(1) {
        int result = app->Loop(5);
        if (result != 0) {
            // Exit the loop, done here.
            break;
        }
    }

    delete app;
    return 0;

}