#include "Window.h"
#include <iostream>

bool pick_accelerator()
{
	std::vector<accelerator> accs = accelerator::get_all();
	accelerator chosen_one;

	auto result = std::find_if(accs.begin(), accs.end(),
		[](const accelerator& acc)
		{
			return !acc.is_emulated &&
				acc.supports_double_precision &&
				!acc.has_display;
		});

	if (result != accs.end())
	{
		chosen_one = *(result);
	}

	std::wcout << chosen_one.description << std::endl;
	bool success = accelerator::set_default(chosen_one.device_path);
	return success;
}

int main(int argc, char** argv)
{
#ifndef _DEBUG
	pick_accelerator();
#endif

	ensureDefaults();

	poxels[250 + (py * 250)].enabled = true;
	poxels[200 + (py * 250)].enabled = true;
	poxels[200 + (py * 250)].color.colors.g = 0;

    Start(argc,argv);
}