#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "LaneDetection.h"

int main(int argc, char* argv[])
{
    cxxopts::Options options("mld_crf", "\n== Line Detector ==\n");

    // input parameter
    bool verbose_lm_detction = false;
    bool verbose_seed_gen = false;
    bool verbose_run_crf = false;
    bool verbose_validating = true;
    bool saveLabel(false);

#ifdef WIN32
    std::string img_path = "..\\data\\20120322142840\\";
#else
    std::string img_path = "../data/20120322142840/";
#endif

    options.add_options()
      ("p,path", "data path", cxxopts::value<std::string>(img_path));

    options.add_options()
      ("lm_detction", "verbose lm detction (true|false)", cxxopts::value<bool>(verbose_lm_detction));

    options.add_options()
      ("seed_gen", "verbose seed gen (true|false)", cxxopts::value<bool>(verbose_seed_gen));

    options.add_options()
      ("run_crf", "verbose run crf (true|false)", cxxopts::value<bool>(verbose_run_crf));

    options.add_options()
      ("validating", "verbose validating (true|false)", cxxopts::value<bool>(verbose_validating));

    options.add_options()
      ("saveLabel", "save Label (true|false)", cxxopts::value<bool>(saveLabel));

    bool help(false);

    options.add_options()
      ("h,help", "display this help", cxxopts::value<bool>(help));

    if(argc > 1)
        options.parse(argc, argv);
    else {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if(help) {
        std::cout << options.help() << std::endl;
        return 0;
    }

	bool verbose = verbose_lm_detction | verbose_seed_gen | verbose_run_crf | verbose_validating;

	//<-------------- Common Variables definition & initialization --------------> 

	LaneDetection ld = LaneDetection();
	std::string img_name = (std::string(img_path)).append(std::to_string(1)).append(".jpg");
	
	// initilaize
    if (!ld.initialize_variable(img_name))
        return -1;
	
	// process
    for(int ff=1; ff < 30; ff++) {

		std::string img_name = (std::string(img_path)).append(std::to_string(ff)).append(".jpg");

		// Initlaization
        if (!ld.initialize_Img(img_name))
			continue;
		
		// detecting lane markings
		ld.lane_marking_detection(verbose_lm_detction);

		// supermarking generation and low-level association
		ld.seed_generation(verbose_seed_gen);

		// CRF graph configuration & optimization using hungarian method
		ld.graph_generation(verbose_run_crf);
		
		// validating
		ld.validating_final_seeds(verbose_validating);
	
        if (verbose)
			cv::waitKey(0);
	}
}
