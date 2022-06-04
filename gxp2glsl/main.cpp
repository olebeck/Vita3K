#include <iostream>

#include <shader/spirv_recompiler.h>
#include <util/fs.h>


void gxp_to_glsl_from_filepath(const std::string &shader_filepath) {
    const fs::path shader_filepath_str{ shader_filepath };
    std::ifstream gxp_stream(shader_filepath, std::ifstream::binary);

    if (!gxp_stream.is_open())
        return;

    const auto gxp_file_size = fs::file_size(shader_filepath_str);
    const auto gxp_program = static_cast<SceGxmProgram *>(calloc(gxp_file_size, 1));

    gxp_stream.read(reinterpret_cast<char *>(gxp_program), gxp_file_size);

    FeatureState features;
    features.direct_fragcolor = false;
    features.support_shader_interlock = true;

    auto output = shader::convert_gxp_to_glsl(*gxp_program, shader_filepath_str.filename().string(), features, nullptr, false, true, nullptr);
    std::cout << std::endl;
    
    auto output_name = shader_filepath_str.filename().string() + ".glsl";
    std::ofstream output_stream(output_name, std::ofstream::binary);
    output_stream << output;
    output_stream.close();

    free(gxp_program);
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <gxp_file>" << std::endl;
        return 1;
    }

    gxp_to_glsl_from_filepath(argv[1]);

    return 0;
}
