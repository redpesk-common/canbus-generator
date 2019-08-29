#include <string>
#include <map>
#include <iostream>

enum class states
{
    NATIVE,
    NEW,
    PROCESSED
};

typedef std::map<std::string, states> map_decoders;
typedef std::pair<std::string,states> pair_decoder;

class decoder_t
{
    public:
        static std::string patchs_;
        static map_decoders decoders_states_;
        static void init_decoder();
        static std::string add_decoder(std::string decoder, std::string version_file, std::string version_low_can);
        static std::string patch_version(std::string decoder, std::string version_file, std::string version_low_can);
        static std::string generate_name_decoder(std::string decoder, std::string version_file, std::string version_low_can);
        static std::string apply_patch();


        static void v1_to_v2(std::string decoder);
};
