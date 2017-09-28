//
// Copyright 2017 Giovanni Mels
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "CommandLine.hh"

namespace n3 {

	CommandLine CommandLine::parse(int argc, char *argv[])
	{
		CommandLine opt;
		
		bool error = false, stop = false;
		for (int i = 1; i < argc && !error; i++) {
			std::string arg = argv[i];
			if (!stop) {
				if (arg.find("-o") == 0) {
					if (arg[2] == '=')
						opt.output = arg.substr(3);
					else {
						opt.output = arg.substr(2);
						
						if (opt.output->empty() && i + 1 < argc)
							opt.output = std::string(argv[++i]);
					}
					error = opt.output->empty();
				} else if (arg.find("-b") == 0) {
					if (arg[2] == '=')
						opt.base = arg.substr(3);
					else {
						opt.base = arg.substr(2);
						
						if (opt.base->empty() && i + 1 < argc)
							opt.base = std::string(argv[++i]);
					}
					error = opt.base->empty();
				} else if (arg == "-h") {
					opt.help = true;
				} else if (arg == "--") {
					stop = true;
				} else if (arg.length() > 1 && arg[0] == '-') {
					error = true;
				} else {
					opt.inputs.push_back(arg);
				}
			} else {
				opt.inputs.push_back(arg);
			}
		}
		
		if (opt.inputs.empty())
			opt.inputs.push_back("-");
		
		opt.error = error;
		
		return opt;
	}

}
