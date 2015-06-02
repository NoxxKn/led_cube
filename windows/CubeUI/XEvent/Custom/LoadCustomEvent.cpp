#include <sstream>
#include <fstream>
#include "LoadCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void LoadCustomEvent::trigger() {
	Application * app = Application::getInstance();
	stringstream ss;

	// load custom Name
	string customName = mCustomName;
	string fileName = mFile;
	
	// execute
	std::ifstream file(fileName);
	if (file) {
		// load
		if (file.good()) {
			CustomEffect * ef= new CustomEffect(customName);
			CubeControl con;
			size_t counter = 0;
			size_t counter_layer = 0;
			
			ss << file.rdbuf();

			while (ss >> con.layer_f[counter]) {
				counter++;

				if (counter == 8) {
					counter = 0;
					ef->addLayer();
					ef->control(counter_layer) = con;
					counter_layer++;
				}
			}

			if (counter_layer > 0)
				app->addEffect(ef);
			else
				delete ef;
		}
		else 
			cout << "Error file loading" << endl;

		file.close();
	}
	else
		cout << "File does not exist" << endl;
}