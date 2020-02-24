#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <utility>

#include "ElfFile.h"
#include "Path.h"

TEST(ElfFile, GetFunctions) {
  std::string executable_path = Path::GetExecutablePath();
  std::string test_elf_file = executable_path + "/testdata/hello_world_elf";

  auto elf_file = ElfFile::Create(test_elf_file.c_str());
  ASSERT_NE(elf_file, nullptr);

  Pdb pdb;
  std::vector<Function> functions;
  ASSERT_TRUE(elf_file->GetFunctions(&pdb, &functions));
  EXPECT_EQ(functions.size(), 10);
  const Function* function = &functions[0];

  EXPECT_EQ(function->Name(), "deregister_tm_clones");
  EXPECT_EQ(function->PrettyName(), "deregister_tm_clones");
  EXPECT_EQ(function->Address(), 0x1080);
  EXPECT_EQ(function->Size(), 0);
  EXPECT_EQ(function->GetPdb(), &pdb);

  function = &functions[9];
  EXPECT_EQ(function->Name(), "main");
  EXPECT_EQ(function->PrettyName(), "main");
  EXPECT_EQ(function->Address(), 0x1135);
  EXPECT_EQ(function->Size(), 35);
  EXPECT_EQ(function->GetPdb(), &pdb);
}

TEST(ElfFile, IsAddressInTextSection) {
  std::string executable_path = Path::GetExecutablePath();
  std::string test_elf_file = executable_path + "/testdata/hello_world_elf";

  auto elf_file = ElfFile::Create(test_elf_file.c_str());
  ASSERT_NE(elf_file, nullptr);

  EXPECT_FALSE(elf_file->IsAddressInTextSection(0x104F));
  EXPECT_TRUE(elf_file->IsAddressInTextSection(0x1050));
  EXPECT_TRUE(elf_file->IsAddressInTextSection(0x11C0));
  EXPECT_FALSE(elf_file->IsAddressInTextSection(0x11C1));
}