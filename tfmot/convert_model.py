import os

def convert_tflite_to_cpp_header(tflite_model_path, output_header_path, array_name="g_model"):
    """
    Converts a TFLite model file into a C++ header file containing a hex array.
    """
    if not os.path.exists(tflite_model_path):
        print(f"Error: TFLite model not found at {tflite_model_path}")
        return

    with open(tflite_model_path, 'rb') as f:
        model_content = f.read()

    hex_array = []
    for byte in model_content:
        hex_array.append(f'0x{byte:02x}')

    cpp_array_lines = []
    for i in range(0, len(hex_array), 12):
        cpp_array_lines.append("    " + ", ".join(hex_array[i:i+12]))
    
    cpp_array_declaration = f"const unsigned char {array_name}[] = {{\n" \
                            + ",\n".join(cpp_array_lines) \
                            + "\n}}";

    with open(output_header_path, 'w') as f:
        f.write("#ifndef TFLITE_MODEL_H\n")
        f.write("#define TFLITE_MODEL_H\n\n")
        f.write(cpp_array_declaration)
        f.write(f"\nconst unsigned int {array_name}_len = {len(model_content)};\n\n")
        f.write("#endif // TFLITE_MODEL_H\n")

    print(f"Successfully converted {tflite_model_path} to {output_header_path}")

# Define paths relative to the current script's directory (tfmot folder)
tflite_model_name = "traffic_sign_final_int8.tflite"
output_header_name = "model_data.h"

# Get the directory where the script is located
script_dir = os.path.dirname(__file__)
tflite_model_path = os.path.join(script_dir, tflite_model_name)
output_header_path = os.path.join(script_dir, output_header_name)

convert_tflite_to_cpp_header(tflite_model_path, output_header_path)
