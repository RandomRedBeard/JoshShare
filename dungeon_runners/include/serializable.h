/**
 * @file serializable.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <jansson.h>

namespace DR {
    struct Serializable {
        virtual json_t* to_json(json_t*) const noexcept = 0;
        inline json_t* new_json() const noexcept {
            json_t* root = json_object();
            return to_json(root);
        }
        virtual void from_json(const json_t*) = 0;

        template<typename T>
        static T from_json(const json_t* o) {
            T t;
            t.from_json(o);
            return t;
        }

        void print() const noexcept {
            json_t* o = new_json();
            char* buf = json_dumps(o, JSON_INDENT(4));
            puts(buf);
            free(buf);
            json_decref(o);
        }

    };
} // namespace DR
