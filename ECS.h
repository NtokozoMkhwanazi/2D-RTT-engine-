#pragma once
#include <unordered_map>
#include <typeindex>
#include <vector>

using Entity = unsigned int;

class ECSRegistry {
    Entity nextEntity = 0;
    std::unordered_map<std::type_index, std::unordered_map<Entity, void*>> components;

public:
    Entity createEntity() { return nextEntity++; }

    template<typename T>
    void addComponent(Entity e, const T& comp) {
        components[typeid(T)][e] = new T(comp);
    }

    template<typename T>
    T* getComponent(Entity e) {
        auto& map = components[typeid(T)];
        if (map.find(e) != map.end()) return static_cast<T*>(map[e]);
        return nullptr;
    }

    template<typename T>
    std::vector<std::pair<Entity, T*>> getAll() {
        std::vector<std::pair<Entity, T*>> result;
        for (auto& [ent, comp] : components[typeid(T)]) {
            result.push_back({ent, static_cast<T*>(comp)});
        }
        return result;
    }
};

