
#include <iostream>
#include <string>
#include <map>
#include "SampleScene.h"
#include "MyFramework.h"

enum ArgErrorCode { NOT_PROVIDED, INVALID };
int main(int argc, char* argv[])
{
	int counter;
	int argErrCode = 0;
	for (counter = 0; counter < argc; counter++)
	{
		if (_strcmpi(argv[counter], "-window") == 0)
		{
			++counter;
			if (counter < argc)
			{
				int w, h;
				sscanf_s(argv[counter], "%dx%d", &w, &h);
				if (w >= 400 && h >= 300)
				{
					MyFramework::width = w;
					MyFramework::height = h;
				}
				else
					argErrCode = ArgErrorCode::INVALID;
			}
			else
				argErrCode = ArgErrorCode::NOT_PROVIDED;
			if (argErrCode)
				std::cout << "You Must Provide Resolution like 800x600 after -window arg Using Defaults... " << std::endl;
		}
	}
	MyFramework::setScene(new SampleScene);
	return run(new MyFramework);
}
