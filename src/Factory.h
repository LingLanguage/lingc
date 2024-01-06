#ifndef FACTORY_H__
#define FACTORY_H__

#include "Context.h"

E_Function Factory_Function(Context *ctx, string name, string belongTypeName, string returns[], byte returns_count, string params[], byte params_count) {

    E_Function func;
    func.id = ctx->static_functions_idRecord++;
    func.index = ctx->static_functions_count++;
    func.name = name;
    func.belongTypeName = belongTypeName;
    func.returns_count = returns_count;
    for (int i = 0; i < returns_count; i++) {
        func.returns[i] = returns[i];
    }
    func.params_count = params_count;
    for (int i = 0; i < params_count; i++) {
        func.params[i] = params[i];
    }

    return func;

}

#endif