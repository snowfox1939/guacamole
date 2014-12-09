/******************************************************************************
 * guacamole - delicious VR                                                   *
 *                                                                            *
 * Copyright: (c) 2011-2013 Bauhaus-Universität Weimar                        *
 * Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de      *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify it    *
 * under the terms of the GNU General Public License as published by the Free *
 * Software Foundation, either version 3 of the License, or (at your option)  *
 * any later version.                                                         *
 *                                                                            *
 * This program is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   *
 * for more details.                                                          *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with this program. If not, see <http://www.gnu.org/licenses/>.             *
 *                                                                            *
 ******************************************************************************/

#ifndef GUA_SKELETAL_ANIMATION_DIRECTOR_HPP
#define GUA_SKELETAL_ANIMATION_DIRECTOR_HPP

// guacamole headers
#include <gua/platform.hpp>
 #include <gua/renderer/RenderContext.hpp>
#include <gua/renderer/BoneTransformUniformBlock.hpp>
#include <gua/utils/Timer.hpp>

// external headers
#include <scm/gl_core.h>
#include <scm/core/math/quat.h>
#include <gua/renderer/SkeletalAnimationUtils.hpp>
#include <vector>
#include <map>
#include <assimp/scene.h>       // Output data structure

namespace gua {

class SkeletalAnimationDirector{
 public:

  SkeletalAnimationDirector(aiScene const*);
  inline ~SkeletalAnimationDirector(){};

  uint getBoneID(std::string const& name);
  void updateBoneTransforms(RenderContext const& ctx);

  void add_animations(aiScene const* scene);

  void add_hierarchy(aiScene const* scene);

private:

  void calculate_pose(float TimeInSeconds, std::shared_ptr<SkeletalAnimation> const& pAnim, std::vector<scm::math::mat4f>& Transforms);

  std::map<std::string,uint> bone_mapping_; // maps a bone name to its index
  uint num_bones_;

  std::shared_ptr<BoneTransformUniformBlock> bone_transforms_block_;

  std::vector<std::shared_ptr<SkeletalAnimation>> animations_;
  std::shared_ptr<SkeletalAnimation> currAnimation_;

  std::shared_ptr<Node> root_;

  bool firstRun_;
  bool hasAnims_;

  Timer timer_;
};

}

#endif  // GUA_SKELETAL_ANIMATION_DIRECTOR_HPP
