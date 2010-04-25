/*
This file is part of Freedom to Smash.
Copyright (C) 2009 Jon Ander Peñalba <jonan88@gmail.com>

Freedom to Smash is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#include <boot.hpp>

// Ogre
#include <OgreConfigFile.h>
#include <OgreRenderSystem.h>
#include <OgreRoot.h>

// FtS
#include <input.hpp>

// Defines where resources are (according to resources.cfg).
void defineResources(void)
{
    using Ogre::ConfigFile;

    Ogre::String section_name, type_name, arch_name;
    ConfigFile file;

    file.load("resources.cfg");
    ConfigFile::SectionIterator section = file.getSectionIterator();
    while (section.hasMoreElements()) {
        section_name = section.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = section.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); i++) {
            type_name = i->first;
            arch_name = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch_name, type_name, section_name);
        }
    }
}

// Setups Ogre's render system.
void setupRenderSystem(Ogre::Root &ogre_root)
{
    // Try to use previous configuration (stored in ogre.cfg)
    if (!ogre_root.restoreConfig()) {
        // If there's no configuration file set defaults
        Ogre::RenderSystem *render_system = ogre_root.getRenderSystemByName("OpenGL Rendering Subsystem");
        ogre_root.setRenderSystem(render_system);
        render_system->setConfigOption("Full Screen", "No");
        render_system->setConfigOption("Video Mode", "800 x 600");
        ogre_root.saveConfig();
    }
    ogre_root.initialise(true, "Freedom to Smash");
}

// Initializes all the resources the program will need.
void initializeAllResources(void)
{
    /// @todo Don't load all resources, load them as they are needed.
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

// Loads all the necessary things for the game to run.
void boot(void)
{
    // Start Ogre
    Ogre::Root *ogre_root = new Ogre::Root;
    defineResources();
    setupRenderSystem(*ogre_root);
    initializeAllResources();
    // Start capturing all input
    Input::getInstance();
}

// Shuts down all the systems and frees memory.
void quit(void)
{
    delete Ogre::Root::getSingletonPtr();
}
