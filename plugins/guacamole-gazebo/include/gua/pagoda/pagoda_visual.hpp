#ifndef GUACAMOLE_PAGODA_VISUAL_H
#define GUACAMOLE_PAGODA_VISUAL_H

#include <gazebo/common/Console.hh>
#include <gazebo/common/common.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/rendering/Visual.hh>
#include <gua/node/Node.hpp>
#include <gua/node/TransformNode.hpp>
#include <gua/renderer/TriMeshLoader.hpp>
#include <memory>

class PagodaVisual;
class PagodaScene;

typedef std::shared_ptr<PagodaVisual> ptr_visual;

class PagodaVisual
{
  public:
    enum VisualType
    {
        VT_ENTITY,
        VT_MODEL,
        VT_LINK,
        VT_VISUAL
    };

    PagodaVisual(const std::string &name, ptr_visual parent);
    ~PagodaVisual();

    void set_id(uint32_t _id);
    void set_name(const std::string &name);
    void set_type(VisualType _type);

    uint32_t get_id() const;
    std::string get_name() const;
    VisualType get_type() const;
    const gazebo::math::Vector3 &get_scale() const;
    ignition::math::Vector3d get_derived_scale() const;
    const ptr_visual &get_parent() const;

    void update_from_msg(const boost::shared_ptr<const gazebo::msgs::Visual> &msg);

  protected:
    PagodaScene *_scene;
    gua::TriMeshLoader _tml;

    uint32_t _id;
    std::string _name;
    VisualType _type;

    ptr_visual _parent;
    std::vector<ptr_visual> _children;

    ignition::math::Vector3d _scale;
    std::string _mesh_name;
    std::string _sub_mesh_name;

    gua::node::TransformNode _node;

    void set_scale(const gazebo::math::Vector3 &scale);
    void set_pose(const gazebo::math::Pose &pose);

    void update_geom_size(const ignition::math::Vector3d &_scale);
    bool attach_mesh(const std::string &mesh_name, const std::string &sub_mesh = "", bool center_submesh = false, const std::string &obj_name = "");
    void DetachObjects();
};

#endif // GUACAMOLE_PAGODA_VISUAL_H