#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Command {
  std::string text;
  std::string description;
  std::vector<std::string> addl_keywords;
};

struct FoundCommand {
  std::vector<std::string>::size_type keywords_found;
  Command command;
  FoundCommand(std::vector<std::string>::size_type keywords_found, Command command)
      : keywords_found {keywords_found}, command {command} {}
  bool operator < (FoundCommand other) {
    return keywords_found > other.keywords_found;
  }
  bool operator > (FoundCommand other) {
    return keywords_found < other.keywords_found;
  }
};

// TODO
// static const std::vector<std::string> synonyms[] {
//   {"decrease", "lower"},
//   {"increase", "raise"},
//   {"build", "compile"},
//   {"package", "pkg", "packages"},
//   {"list", "find", "search"},
//   {"orphan", "orphaned", "orphans"},
//   {"explicit", "explicitly"},
//   {"own", "owned"}
// };

// TODO: make case insensitive
static const Command commands[] {
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

std::vector<std::string> Split(const std::string& s, char delim = ' ') {
  std::stringstream ss {s};
  std::string part;
  std::vector<std::string> parts;
  while (getline(ss, part, delim)) {
    parts.push_back(part);
  }
  return parts;
}

std::vector<std::string> Union(std::vector<std::string> v1,
                               std::vector<std::string> v2) {
  std::vector<std::string> result;
  set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
  return result;
}

std::vector<std::string> Union(std::vector<std::string> v1,
                               std::vector<std::string> v2,
                               std::vector<std::string> v3) {
  return Union(Union(v1, v2), v3);
}

std::vector<std::string> Intersect(std::vector<std::string>& v1,
                                   std::vector<std::string>& v2) {
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  std::vector<std::string> result;
  set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
  return result;
}

std::vector<FoundCommand> FindCommands(const std::string& input) {
  std::vector<std::string> input_keywords = Split(input);
  std::vector<FoundCommand> results;
  for (Command command : commands) {
    std::vector<std::string> cmd_keywords = Union(Split(command.text),
                                                  Split(command.description),
                                                  command.addl_keywords);
    std::vector<std::string> found_keywords = Intersect(input_keywords, cmd_keywords);
    if (!found_keywords.empty()) {
      results.emplace_back(found_keywords.size(), command);
    }
  }
  return results;
}

int main() {
  std::cout << "Using keywords, describe what you would like to do: ";
  std::string input;
  getline(std::cin, input);
  std::vector<FoundCommand> results = FindCommands(input);
  sort(results.begin(), results.end());
  for (FoundCommand result : results) {
    std::cout << result.command.description << ": " << result.command.text << std::endl;
  }
  return 0;
}
