/*
    This file is a part of SORT(Simple Open Ray Tracing), an open-source cross
    platform physically based renderer.
 
    Copyright (c) 2011-2018 by Cao Jiayin - All rights reserved.
 
    SORT is a free software written for educational purpose. Anyone can distribute
    or modify it under the the terms of the GNU General Public License Version 3 as
    published by the Free Software Foundation. However, there is NO warranty that
    all components are functional in a perfect manner. Without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.
 
    You should have received a copy of the GNU General Public License along with
    this program. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
 */

#pragma once

#include "task.h"
#include "sampler/sample.h"
#include "math/vector2.h"

//! @brief  Render_Task is a basic rendering unit doing ray tracing.
//!
//! Each render task is usually responsible for a tile of image to be rendered in
//! most cases. In other cases, like light tracing, there is no difference between
//! different render_task.
class Render_Task : public Task{
public:
    //! @brief Constructor
    //!
    //! @param priority     New priority of the task.
    Render_Task(const Vector2i& ori , const Vector2i& size , class Scene* scene , class Sampler* sampler , PixelSample* pixelSamples ,
                const char* name , unsigned int priority , const std::unordered_set<std::shared_ptr<Task>>& dependencies ) : 
                Task( name , priority , dependencies ), m_coord(ori), m_size(size), m_scene(*scene), m_sampler( sampler ),
                m_pixelSamples(pixelSamples) {}
    
    //! @brief  Execute the task
    void        Execute() override;

    //! @brief  Get the coordinate of the tile, top-left corner.
    //!
    //! @return Top-left corner of the tile.
    inline Vector2i    GetTopLeft() const {
        return m_coord;
    }
    
    //! @brief  Get the size of the tile.
    //!
    //! @return The size of the current tile.
    inline Vector2i    GetTileSize() const {
        return m_size;
    }

private:
    Vector2i              m_coord;            /**< Top-left corner of the current tile. */
    Vector2i              m_size;             /**< Size of the current tile to be rendered. */
    class Scene&	      m_scene;            /**< Scene for ray tracing. */
    class Sampler*        m_sampler;          /**< Sampler for taking samples. Currently not used. */
    PixelSample*          m_pixelSamples;     /**< Samples to take. Currently not used. */
};
