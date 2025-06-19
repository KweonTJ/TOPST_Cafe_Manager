#include <ros/ros.h>
#include <std_msgs/String.h>
#include <XmlRpcValue.h>
#include <sstream>
#include <map>
#include <vector>
#include <string>

class OrderManager
{
public:
  OrderManager(ros::NodeHandle& nh)
  {
    XmlRpc::XmlRpcValue recipes_xml;
    if (!nh.getParam("recipes", recipes_xml))
    {
      ROS_ERROR("Failed to load 'recipes' parameter");
      ros::shutdown();
      return;
    }
    for (auto it = recipes_xml.begin(); it != recipes_xml.end(); ++it)
    {
      std::string drink = static_cast<std::string>(it->first);
      XmlRpc::XmlRpcValue entry = recipes_xml[drink];

      std::vector<int> seq;
      for (int i = 0; i < entry["sequence"].size(); ++i)
        seq.push_back(static_cast<int>(entry["sequence"][i]));
      recipes_seq_[drink] = seq;

      std::map<std::string,int> ratio;
      XmlRpc::XmlRpcValue rxml = entry["ratios"];
      for (auto rit = rxml.begin(); rit != rxml.end(); ++rit)
      {
        std::string key = static_cast<std::string>(rit->first);
        ratio[key] = static_cast<int>(rxml[key]);
      }
      recipes_ratio_[drink] = ratio;
    }

    sub_order_ = nh.subscribe("order_raw", 1, &OrderManager::orderCallback, this);
    pub_cycle_ = nh.advertise<std_msgs::String>("coffee_cycle", 1);
    pub_ratio_ = nh.advertise<std_msgs::String>("ingredient_ratio", 1);
    ROS_INFO("OrderManager ready");
  }

private:
  void orderCallback(const std_msgs::String::ConstPtr& msg)
  {
    std::string drink = msg->data;
    if (!recipes_seq_.count(drink))
    {
      ROS_WARN("Unknown drink: %s", drink.c_str());
      return;
    }
    const auto& seq = recipes_seq_[drink];
    std_msgs::String seq_msg;
    std::ostringstream oss;
    for (size_t i = 0; i < seq.size(); ++i)
      oss << seq[i] << (i + 1 < seq.size() ? ' ' : '\0');
    seq_msg.data = oss.str();
    pub_cycle_.publish(seq_msg);

    const auto& ratio = recipes_ratio_[drink];
    std::ostringstream oss2;
    bool first = true;
    for (const auto& kv : ratio)
    {
      if (!first) oss2 << ',';
      oss2 << kv.first << ':' << kv.second;
      first = false;
    }
    std_msgs::String ratio_msg;
    ratio_msg.data = oss2.str();
    pub_ratio_.publish(ratio_msg);
  }

  ros::Subscriber sub_order_;
  ros::Publisher  pub_cycle_;
  ros::Publisher  pub_ratio_;
  std::map<std::string, std::vector<int>>          recipes_seq_;
  std::map<std::string, std::map<std::string,int>> recipes_ratio_;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "order_manager");
  ros::NodeHandle nh;
  OrderManager om(nh);
  ros::spin();
  return 0;
}

