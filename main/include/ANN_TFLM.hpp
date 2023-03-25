#ifndef ANN_TFLM_HPP
#define ANN_TFLM_HPP

#include <stdio.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "model.h"

namespace TFLMmodel{
    const tflite::Model* model = nullptr;
    tflite::MicroInterpreter* interpreter = nullptr;
    TfLiteTensor* input = nullptr;
    TfLiteTensor* output = nullptr;

    constexpr int kTensorArenaSize = 2000;
    uint8_t tensor_arena[kTensorArenaSize];

    float predict(float x) {

        model = tflite::GetModel(g_model);
        if (model->version() != TFLITE_SCHEMA_VERSION) {
        MicroPrintf("Model provided is schema version %d not equal to supported "
                    "version %d.", model->version(), TFLITE_SCHEMA_VERSION);
        return 0;
        }

        static tflite::AllOpsResolver resolver;

        static tflite::MicroInterpreter static_interpreter(
            model, resolver, tensor_arena, kTensorArenaSize);
        interpreter = &static_interpreter;

        TfLiteStatus allocate_status = interpreter->AllocateTensors();
        if (allocate_status != kTfLiteOk) {
        MicroPrintf("AllocateTensors() failed");
        return 0;
        }

        input = interpreter->input(0);
        output = interpreter->output(0);

        // Quantize the input from floating-point to integer
        int8_t x_quantized = x / input->params.scale + input->params.zero_point;
        // Place the quantized input in the model's input tensor
        input->data.int8[0] = x_quantized;

        // Run inference, and report any error
        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
            MicroPrintf("Invoke failed on x: %f\n", static_cast<double>(x));
            return 0;
        }

        // Obtain the quantized output from model's output tensor
        int8_t y_quantized = output->data.int8[0];
        // Dequantize the output from integer to floating-point
        float y = (y_quantized - output->params.zero_point) * output->params.scale;
        
        return static_cast<float>(y);
    }
}

#endif