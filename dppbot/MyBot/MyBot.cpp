#include "MyBot.h"
#include <dpp/dpp.h>
#include <iostream>
#include "IpCommand.h"
const std::string    BOT_TOKEN    = "s";

int main() {
    /* Create bot cluster */
    dpp::cluster bot(BOT_TOKEN);

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Handle slash command */
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
         if(event.command.get_command_name() == "ping") {
            event.reply("Pong!");
         }
         if(event.command.get_command_name() == "ip") {
             IpCommand::execute(event, std::get<std::string>(event.get_parameter("ip")));
         }
    });

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("ip", "Grab IP information", bot.me.id).add_option(
                dpp::command_option(dpp::co_string, "ip", "The IP to fetch"))
            );
        }
    });

    /* Start the bot */
    bot.start(dpp::st_wait);

    return 0;
}
