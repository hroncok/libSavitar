#include "Scene.h"
#include "../pugixml/src/pugixml.hpp"
#include <iostream>
#include <string>
using namespace Savitar;

Scene::Scene()
{

}

Scene::~Scene()
{

}

std::vector< SceneNode > Scene::getSceneNodes()
{
    return this->scene_nodes;
}

void Scene::addSceneNode(SceneNode node)
{
    this->scene_nodes.push_back(node);
}


void Scene::fillByXMLNode(pugi::xml_node xml_node)
{
    pugi::xml_node resources = xml_node.child("resources");

    pugi::xml_node build = xml_node.child("build");
    for(pugi::xml_node item = build.child("item"); item; item = item.next_sibling("item"))
    {
        // Found a item in the build. The items are linked to objects by objectid.
        pugi::xml_node object_node = resources.find_child_by_attribute("object", "id", item.attribute("objectid").value());
        if(object_node)
        {
            SceneNode temp_scene_node = createSceneNodeFromObject(xml_node, object_node);
            temp_scene_node.setStransformation(item.attribute("transform").as_string());
            scene_nodes.push_back(temp_scene_node);
        }
        else
        {
            // TODO: add proper error handling
            std::cout << "Could not find object by given ID" << std::endl;
        }
    }
}

SceneNode Scene::createSceneNodeFromObject(pugi::xml_node root_node, pugi::xml_node object_node)
{
    pugi::xml_node components = object_node.child("components");
    SceneNode scene_node;
    scene_node.fillByXMLNode(object_node);

    // We have to do the checking for children outside of the SceneNode creation itself, because it only has references.
    if(components)
    {
        for(pugi::xml_node component = components.child("component"); component; component = component.next_sibling("component"))
        {
            // This node has children. Add them one by one.
            pugi::xml_node child_object_node = root_node.child("resources").find_child_by_attribute("object", "id", component.attribute("objectid").value());
            if(child_object_node)
            {
                SceneNode child_node = createSceneNodeFromObject(root_node, child_object_node);
                child_node.setStransformation(component.attribute("transform").as_string());
                scene_node.addChild(child_node);
            } else
            {
                // TODO: ADD proper error handling here.
                std::cout << "Child_object_node not found :( " << std::endl;
            }
        }
    }
    return scene_node;
}


