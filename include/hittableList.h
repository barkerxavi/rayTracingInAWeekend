#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "hittable.h"
#include <headderMain.h>

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittableList : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittableList() {}
        hittableList(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray& r, interval rayT, hitRecord& rec) const override {
            hitRecord tempRec;
            bool hitAnything = false;
            auto closestSoFar = rayT.max;

            for (const auto& object : objects) {
                if (object->hit(r, interval(rayT.min, closestSoFar), tempRec)) {
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }
};



#endif