#include "decoder.hpp"

map_decoders decoder_t::decoders_states_;
std::string decoder_t::patchs_;


void decoder_t::init_decoder()
{
    decoder_t::decoders_states_.insert(pair_decoder("decoder_t::decode_state", states::NATIVE));
    decoder_t::decoders_states_.insert(pair_decoder("decoder_t::decode_boolean", states::NATIVE));
    decoder_t::decoders_states_.insert(pair_decoder("decoder_t::decode_ignore", states::NATIVE));
    decoder_t::decoders_states_.insert(pair_decoder("decoder_t::decode_noop", states::NATIVE));
    decoder_t::decoders_states_.insert(pair_decoder("decoder_t::decode_bytes", states::NATIVE));
    decoder_t::decoders_states_.insert(pair_decoder("decoder_t::decode_obd2_response", states::NATIVE));
}


std::string decoder_t::add_decoder(std::string decoder, std::string version_file, std::string version_low_can)
{
    if(decoder.compare("nullptr"))
    {
        if ( decoder_t::decoders_states_.find(decoder) == decoder_t::decoders_states_.end() ) { // Not found signal
            decoder_t::decoders_states_.insert(pair_decoder(decoder,states::NEW));
            std::string ret = decoder_t::patch_version(decoder,version_file,version_low_can);
            decoder_t::decoders_states_[decoder] = states::PROCESSED;
            return ret;
        }
        else
        {
            if(decoder_t::decoders_states_[decoder] == states::PROCESSED)
            {
                return decoder_t::patch_version(decoder,version_file,version_low_can);
            }
        }
    }
    return decoder;
}


std::string decoder_t::patch_version(std::string decoder, std::string version_file, std::string version_low_can)
{
    std::size_t pos = version_file.find(".");
    int main_value_version_file = std::stoi(version_file.substr(0,pos));

    std::size_t pos2 = version_low_can.find(".");
    int main_value_version_low_can = std::stoi(version_low_can.substr(0,pos2));
    if(main_value_version_file != main_value_version_low_can) // Not same version
    {
        if(decoder_t::decoders_states_[decoder] == states::NEW)
        {
            if(main_value_version_low_can == 2)
            {
                if(main_value_version_file == 1)
                {
                    decoder_t::v1_to_v2(decoder); // add wrap
                }
                else
                {
                    throw "Version not implemented";
                }
            }
            else
            {
                throw "Version not implemented";
            }
        }
        return decoder_t::generate_name_decoder(decoder,version_file,version_low_can);
    }
    else
    {
        return decoder;
    }
}

std::string decoder_t::generate_name_decoder(std::string decoder, std::string version_file, std::string version_low_can)
{
    std::size_t pos = version_file.find(".");
    std::string main_value_version_file = version_file.substr(0,pos);
    std::size_t pos2 = version_low_can.find(".");
    std::string main_value_version_low_can = version_low_can.substr(0,pos2);
    return decoder+"_v"+main_value_version_file+"_to_v"+main_value_version_low_can;
}

std::string decoder_t::apply_patch()
{
    return decoder_t::patchs_;
}

void decoder_t::v1_to_v2(std::string decoder)
{
    std::string patch = "";
    patch = patch + "openxc_DynamicField "+decoder+"_v1_to_v2(signal_t& signal, std::shared_ptr<message_t> message, bool* send){\n";
    patch = patch + "\tfloat value = decoder_t::parse_signal_bitfield(signal, message);\n";
    patch = patch + "\topenxc_DynamicField ret = "+decoder+"(signal, value, send);\n";
    patch = patch + "\tif ((signal.get_last_value() == value && !signal.get_send_same()) || !*send ){\n";
    patch = patch + "\t\t*send = false;\n";
    patch = patch + "\t}\n";
    patch = patch + "\tsignal.set_last_value(value);\n";
    patch = patch + "\treturn ret;\n";
    patch = patch + "}\n";

    decoder_t::patchs_ = decoder_t::patchs_ + "\n" + patch;
}
