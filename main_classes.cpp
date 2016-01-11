#include <iostream>
#include <string>
#include <vector>

class Command {
 public:
  Command(const std::string& text,
          const std::string& description,
          const std::vector<std::string> keywords)
      : text_{text}, description_{description}, keywords_{keywords} {}

  std::string ToString() const {
    return description_ + ": " + text_;
  }

  bool Find(const std::string& word) const {
    if (text_.find(word) != std::string::npos
        || description_.find(word) != std::string::npos) {
      return true;
    }
    for (const auto& keyword : keywords_) {
      if (keyword.find(word) != std::string::npos) {
        return true;
      }
    }
    return false;
  }

 private:
  std::string text_;
  std::string description_;
  std::vector<std::string> keywords_;
};

class Commands {
 public:
  Commands(std::initializer_list<Command> commands) : commands_{commands} {}

  template<class InputIt>
  std::vector<std::string> Find(InputIt first, InputIt last) const {
    std::vector<std::string> results;
    for (const auto& command : commands_) {
      for (auto it = first; it != last; ++it) {
        if (command.Find(*it)) {
          results.emplace_back(command.ToString());
          break;
        }
      }
    }
    return results;
  }

 private:
  std::vector<Command> commands_;
};

int main(int argc, char *argv[]) {
  // TODO: make case insensitive
  // TODO: sort by match
  const Commands commands{
    {"amixer -Mq set Master 1%-", "decrease volume", {"lower"}},
    {"amixer -Mq set Master 1%+", "increase volume", {"raise"}},
    {"makepkg -sri", "build and install a package using a PKGBUILD file", {"pkgbuild"}},
    {"makepkg -efi", "rebuild and reinstall a package using a PKGBUILD file",
      {"build", "install", "pkgbuild"}},
    {"pacman -Qdt", "list orphaned packages", {"find", "orphan"}},
    {"pacman -Qe", "list explicitly installed packages", {"find", "explicit"}},
    {"pacman -Ql [package]", "list files owned by package", {"find", "own"}},
    {"pacman -Qo [file]", "list packages that own file", {"find", "owned"}}
  };
  for (const auto& command : commands.Find(&argv[0], &argv[argc])) {
    std::cout << command << std::endl;
  }
  return 0;
}
