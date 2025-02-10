#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "board_shim.h"

using namespace std;

bool parse_args (int argc, char *argv[], std::vector<MindRoveInputParams> *params);


int main (int argc, char *argv[])
{
    BoardShim::enable_dev_board_logger ();

    std::vector<MindRoveInputParams> params = {};
    std::vector<BoardShim*> boards = {};

    int board_id = 1;
    
    if (!parse_args (argc, argv, &params))
    {
        return -1;
    }
    
    int res = 0;

    

    for(int i = 0; i < params.size(); i++)
    {   
        BoardShim *board = new BoardShim (board_id, params[i]);
        
        boards.push_back(board);

        try
        {
            board->prepare_session ();
            board->start_stream ();
        }
        catch (const MindRoveException &err)
        {
            BoardShim::log_message ((int)LogLevels::LEVEL_ERROR, err.what ());
            res = err.exit_code;
            if (board->is_prepared ())
            {
                board->release_session ();
            }
        }
    }
#ifdef _WIN32
        Sleep (5000);
#else
        sleep (5);
#endif

    for(int i=0; i< boards.size(); i++){
        
        BoardShim *board = boards[i];
        
        try
        {
            board->stop_stream ();
            MindRoveArray<double, 2> data = board->get_current_board_data (10);
            board->release_session ();
            std::cout << "Data from board with mac_address: " << params[i].mac_address << " or idx (ip_port): "<< params[i].ip_port << std::endl;
            std::cout << data << std::endl;
        }
        catch (const MindRoveException &err)
        {
            BoardShim::log_message ((int)LogLevels::LEVEL_ERROR, err.what ());
            res = err.exit_code;
            if (board->is_prepared ())
            {
                board->release_session ();
            }
        }
    }


    for(int i=0; i< boards.size(); i++){
        delete boards[i];
    }

    return res;
}

bool parse_args (int argc, char *argv[], std::vector<MindRoveInputParams> *params)
{
    bool board_id_found = false;

    int port_idx = 0;
    int timeout_idx = 0;
    int mac_idx = 0;

    for (int i = 1; i < argc; i++)
    {

        if (std::string (argv[i]) == std::string ("--ip-port"))
        {
            if (i + 1 < argc)
            {
                i++;

                if (params->size() < port_idx + 1)
                {
                    MindRoveInputParams new_params;
                    params->push_back(new_params);
                }

                params->at(port_idx).ip_port = std::stoi (std::string (argv[i]));
                port_idx++;
            }
            else
            {
                std::cerr << "missed argument" << std::endl;
                return false;
            }
        }

        if (std::string (argv[i]) == std::string ("--timeout"))
        {
            if (i + 1 < argc)
            {
                i++;
                if (params->size() < timeout_idx + 1)
                {
                    MindRoveInputParams new_params;
                    params->push_back(new_params);
                }
                params->at(timeout_idx).timeout = std::stoi (std::string (argv[i]));
                timeout_idx++;
            }
            else
            {
                std::cerr << "missed argument" << std::endl;
                return false;
            }
        }

        if (std::string (argv[i]) == std::string ("--mac-address"))
        {
            if (i + 1 < argc)
            {
                i++;

                if(params->size() < mac_idx + 1)
                {
                    MindRoveInputParams new_params;
                    params->push_back(new_params);
                }
                params->at(mac_idx).mac_address = std::string (argv[i]);
                mac_idx++;
            }
            else
            {
                std::cerr << "missed argument" << std::endl;
                return false;
            }
        }

    }
    if (mac_idx == 0 && port_idx == 0)
    {
        std::cerr << "Provide a way to select devices connected to the Syncbox" << std::endl;
        std::cerr << "For example if you want to connect to 3 devices (ex. MindRove_ARB_abc123, MindRove_ARC_def456 and MindRove_ARB_ghi789) use the following command: " << std::endl;
        std::cerr << "./syncbox_get_data --mac-address abc123 --mac-address def456 --mac-address ghi789" << std::endl;
        return false;
    }
    return true;
}