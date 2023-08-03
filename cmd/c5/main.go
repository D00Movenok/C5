package main

import (
	"errors"
	"fmt"
	"os"
	"time"

	"github.com/rs/zerolog"
	"github.com/rs/zerolog/log"
	"github.com/spf13/pflag"
)

const banner = `
Here will be a beautiful banner later.

v%s @d00movenok

:: C5 - command & control custom communication channels.

`

var (
	version = "0.0.0-next"

	logFile = pflag.StringP(
		"log",
		"l",
		"c5.log",
		"Path to the log file",
	)
	verbose = pflag.BoolP(
		"verbose",
		"v",
		false,
		"Verbose logging",
	)
)

func main() {
	fmt.Fprintf(os.Stdout, banner[1:], version)

	initPflag()
	initLogger()
	setLogLevel()

	log.Info().Msg("Shutdown successful")
}

func initPflag() {
	pflag.ErrHelp = errors.New("") //nolint:reassign // remove error from output
	pflag.Usage = func() {
		fmt.Fprintln(os.Stdout, "Usage of C5:")
		pflag.PrintDefaults()
	}
	pflag.Parse()
}

func initLogger() {
	zerolog.TimeFieldFormat = zerolog.TimeFormatUnix

	fileWriter, err := os.OpenFile(
		*logFile,
		os.O_WRONLY|os.O_CREATE|os.O_APPEND,
		0600,
	)
	if err != nil {
		log.Fatal().Err(err).Msg("Can't create/open log file")
	}
	consoleWriter := zerolog.ConsoleWriter{
		Out:        os.Stderr,
		TimeFormat: time.RFC3339,
	}

	log.Logger = log.Output(zerolog.MultiLevelWriter(consoleWriter, fileWriter))
}

func setLogLevel() {
	if *verbose {
		zerolog.SetGlobalLevel(zerolog.DebugLevel)
	} else {
		zerolog.SetGlobalLevel(zerolog.InfoLevel)
	}
}
