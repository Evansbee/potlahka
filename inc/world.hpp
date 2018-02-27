#prama once

#include "config.hpp"
#include "hittable.hpp"

#include <vector>
#include <memory>
class world : public hittable
{
   public:
      virtual bool hit(const ray& r, real tmin, real tmax, hit_recort &record) const override;
   private:
      std::vector<std::unique_ptr<hittable>> m_Entities;
};

bool world::hit(const ray& r, real tmin, real tmax, hit_record &record) const
{
   return false;
}
