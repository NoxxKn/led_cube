#include <sstream>
#include <fstream>
#include "SaveCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void SaveCustomEvent::trigger() {
	Application * app = Application::getInstance();

	// load custom Name
	string customName = mCustomName;
	string fileName = mFileName;

	// lock mutex
	mutex * m = app->cubesMutex();

	// execute
	std::ofstream file(fileName);
	if (file) {
		// load
		if (file.good()) {
			m->lock();
			CubeControl con;
			size_t counter = 0;
			size_t counter_layer = 0;

			bool found = false;
			list<IEffect*> * effects = app->effects();
			list<IEffect*>::iterator etr;
			CustomEffect * custom = NULL;
			for (etr = effects->begin(); etr != effects->end(); ++etr) {
				IEffect * ef = *etr;
				if (ef->type() == ET_CUSTOM) {
					CustomEffect * ce = (CustomEffect*)ef;
					if (customName == ce->name())
						custom = ce;
				}
			}

			if (custom) {
				counter_layer = custom->sizeLayers();
				for (size_t i = 0; i < counter_layer; ++i) {
					con = custom->control(i);
					for (size_t j = 0; j < 8; ++j)
						file << con.layer_f[j] << endl;
				}
			}

			m->unlock();
		}
		else
			cout << "Error opening file" << endl;

		file.close();
	}
	else
		cout << "File does not exist" << endl;
}