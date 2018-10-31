#include <algorithm>
#include <chrono>
#include <string>

#if defined(_OPENMP)
#include <omp.h>
#endif

#include "command_line.h"
#include "computations.h"
#include "utils.h"

/******************************************************************************
 * Time measurement primitives.
 */
template <typename Rep, typename Period>
static std::string duration_string (std::chrono::duration<Rep, Period> duration) {
	namespace chrono = std::chrono;
	using chrono::duration_cast;
	const auto hours = duration_cast<chrono::hours> (duration).count ();
	if (hours > 10) {
		return fmt::format ("{}h", hours);
	}
	const auto minutes = duration_cast<chrono::minutes> (duration).count ();
	if (minutes > 10) {
		return fmt::format ("{}m", minutes);
	}
	const auto seconds = duration_cast<chrono::seconds> (duration).count ();
	if (seconds > 10) {
		return fmt::format ("{}s", seconds);
	}
	const auto milliseconds = duration_cast<chrono::milliseconds> (duration).count ();
	if (milliseconds > 10) {
		return fmt::format ("{}ms", milliseconds);
	}
	const auto microseconds = duration_cast<chrono::microseconds> (duration).count ();
	if (microseconds > 10) {
		return fmt::format ("{}us", microseconds);
	}
	const auto nanoseconds = duration_cast<chrono::nanoseconds> (duration).count ();
	return fmt::format ("{}ns", nanoseconds);
}

static std::chrono::high_resolution_clock::time_point instant () {
	return std::chrono::high_resolution_clock::now ();
}

/******************************************************************************
 * Program entry point.
 */
int main (int argc, char * argv[]) {
	// Command line parsing setup
	const auto command_line = CommandLineView (argc, argv);
	auto parser = CommandLineParser ();

	parser.flag ({"h", "help"}, "Display this help", [&]() { //
		parser.usage (stderr, command_line.program_name ());
		std::exit (EXIT_SUCCESS);
	});

#if defined(_OPENMP)
	parser.option ({"n", "nb-threads"}, "n", "Number of computation threads (default=max)", [&](string_view n) {
		const auto nb_threads = parse_positive_int (n, "nb threads");
		const auto nb_proc = std::size_t (omp_get_num_procs ());
		if (!(0 < nb_threads && nb_threads <= nb_proc)) {
			throw std::runtime_error (fmt::format ("Number of threads must be in [1, {}]", nb_proc));
		}
		omp_set_num_threads (int(nb_threads));
	});
#endif

	try {
		// Parse command line arguments. All actions declared to the parser will be called here.
		parser.parse (command_line);

	} catch (const CommandLineParser::Exception & exc) {
		fmt::print (stderr, "Error: {}. Use --help for a list of options.\n", exc.what ());
		return EXIT_FAILURE;
	} catch (const std::exception & exc) {
		fmt::print (stderr, "Error: {}\n", exc.what ());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}