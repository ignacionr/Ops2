#pragma once

#include <expected>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace ignacionr::text {
    using command_callback_t = std::function<void(std::string_view)>;
    struct command_source {
        std::function<void(std::string_view, command_callback_t)> list_commands;
        std::function<std::optional<std::expected<std::string, std::string>>(std::string_view)> execute;
    };
    struct command_host
    {
        void register_command(std::string &&name, std::function<std::string()> &&command)
        {
            direct_commands.emplace(std::move(name), std::move(command));
        }
        
        void register_source(command_source &&source)
        {
            sources.emplace_back(std::move(source));
        }

        void list_commands(std::string_view partial, command_callback_t callback)
        {
            for (auto &[name, _] : direct_commands)
            {
                if (name.contains(partial))
                {
                    callback(name);
                }
            }
            for (auto &source : sources)
            {
                source.list_commands(partial, callback);
            }
        }

        std::expected<std::string,std::string> execute(std::string_view command)
        {
            if (auto it = direct_commands.find(std::string(command)); it != direct_commands.end())
            {
                return it->second();
            }
            for (auto &source : sources)
            {
                auto result = source.execute(command);
                if (result)
                {
                    return *result;
                }
            }
            return std::unexpected("Command not found");
        }

        std::map<std::string, std::function<std::string()>> direct_commands;
        std::vector<command_source> sources;
    };
}