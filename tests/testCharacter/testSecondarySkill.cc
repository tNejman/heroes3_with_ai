#include <gtest/gtest.h>

#include "Characters/SecondarySkill.h"

TEST( SecondarySkillTest, createCompleteInstance ) {
  auto secondary_skill1 = SecondarySkill::create( ProjectLib::SecondarySkillType::AIR_MAGIC );
  auto secondary_skill2 = SecondarySkill::create( ProjectLib::SecondarySkillType::FIRE_MAGIC, ProjectLib::SecondarySkillLevel::EXPERT );

  ASSERT_EQ( secondary_skill1->getType(), ProjectLib::SecondarySkillType::AIR_MAGIC );
  ASSERT_EQ( secondary_skill1->getLevel(), ProjectLib::SecondarySkillLevel::BASIC );

  ASSERT_EQ( secondary_skill2->getType(), ProjectLib::SecondarySkillType::FIRE_MAGIC );
  ASSERT_EQ( secondary_skill2->getLevel(), ProjectLib::SecondarySkillLevel::EXPERT );
}

TEST( SecondarySkillTest, copyMethod ) {
  auto secondary_skill1 = SecondarySkill::create( ProjectLib::SecondarySkillType::AIR_MAGIC );
  auto secondary_skill2 = secondary_skill1->copy();

  ASSERT_NE( secondary_skill1, secondary_skill2 );
  ASSERT_EQ( secondary_skill1->getType(), secondary_skill2->getType() );
  ASSERT_EQ( secondary_skill1->getLevel(), secondary_skill2->getLevel() );
}