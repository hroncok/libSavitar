/*
 * This file is part of libSavitar
 *
 * Copyright (C) 2017 Ultimaker b.v. <j.vankessel@ultimaker.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

class SceneNode
{
    %TypeHeaderCode
    #include "SceneNode.h"
    %End
public:
    SceneNode();
    virtual ~SceneNode();

    MeshData& getMeshData();

    std::vector<SceneNode*> getChildren();

    std::string getTransformation();
    void setTransformation(std::string);

    std::map<std::string, std::string> getSettings();
    void setSetting(std::string key, std::string value);

    void addChild(SceneNode* child /Transfer/);
};

