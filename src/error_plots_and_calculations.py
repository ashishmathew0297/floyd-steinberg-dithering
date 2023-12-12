import numpy as np
from matplotlib import pyplot as plt
import matplotlib.ticker as ticker
from matplotlib import rc

rc('text', usetex=True)

serial_dithering_time_small = np.loadtxt('../time_measurements/serial_dithering_time_small.dat')
serial_dithering_time_large = np.loadtxt('../time_measurements/serial_dithering_time_large.dat')

x_serial = serial_dithering_time_small[:,0]

y_serial_small = serial_dithering_time_small[:,1:]
y_serial_large = serial_dithering_time_large[:,1:]


fig_1, axis_1 = plt.subplots(1,2, figsize=(10, 4))
fig_1.tight_layout(pad=4.0)
fig_1.subplots_adjust(wspace=0.275)
axis_1[0].grid(visible=True)
axis_1[0].plot(x_serial, y_serial_small, color='#2aa198', linestyle='-', label=r'$\mathbf{Processing\;Time}$')
axis_1[0].set_xlabel(r'$\mathbf{Iteration}$', fontdict={'color':'#000000'})
axis_1[0].set_ylabel(r'$\mathbf{Time}$', fontdict={'color':'#000000'})
axis_1[0].set_title(r'$\mathbf{Processing\;Times\;for\;a\;Small\;Image}$')
axis_1[0].legend(loc=2)

axis_1[1].grid(visible=True)
axis_1[1].plot(x_serial, y_serial_large, color='#2aa198', linestyle='-', label=r'$\mathbf{Processing\;Time}$')
axis_1[1].set_xlabel(r'$\mathbf{Iteration}$', fontdict={'color':'#000000'})
axis_1[1].set_ylabel(r'$\mathbf{Time}$', fontdict={'color':'#000000'})
axis_1[1].set_title(r'$\mathbf{Processing\;Times\;for\;a\;Large\;Image}$', fontdict={'color':'#000000'})
axis_1[1].legend(loc=2)
plt.savefig("../output/graphs/serial_time_readings.png", dpi=200)


parallel_time_data_large = np.loadtxt('../time_measurements/parallel_dithering_time_large.dat')
parallel_time_data_small = np.loadtxt('../time_measurements/parallel_dithering_time_small.dat')

number_of_threads = parallel_time_data_large[:,0]

strong_scaling_times_large = np.mean(parallel_time_data_large[:,1:], axis=1)
strong_scaling_times_small = np.mean(parallel_time_data_small[:,1:], axis=1)

# Calculating Speedup = T1/Tp
strong_scaling_speedup_large = np.full_like(strong_scaling_times_large, strong_scaling_times_large[0])/strong_scaling_times_large
strong_scaling_speedup_small = np.full_like(strong_scaling_times_small, strong_scaling_times_small[0])/strong_scaling_times_small

print(strong_scaling_speedup_large)
print(strong_scaling_speedup_small)

fig_2, axis_2 = plt.subplots()
axis_3 = axis_2.twinx()
ln1 = axis_2.plot(number_of_threads, strong_scaling_speedup_large, color='#b58900', linestyle='-', label=r'$\mathbf{Speedup\;for\;a\;large\;image}$')
ln2 = axis_3.plot(number_of_threads, strong_scaling_speedup_small, color='#2aa198', linestyle='-', label=r'$\mathbf{Speedup\;for\;a\;small\;image}$')
ln3 = axis_2.plot(number_of_threads[0:2], number_of_threads[0:2], color='#dc322f', linestyle='-', label=r'$\mathbf{Ideal\;Speedup}$')
axis_2.set_xlabel('$\mathbf{Number\;of\;Processors\;(p)}$', fontdict={'color':'#000000'})
axis_2.set_ylabel(r'$\mathbf{Speedup}$', fontdict={'color':'#b58900'})
axis_3.set_ylabel(r'$\mathbf{Speedup}$', fontdict={'color':'#2aa198'})
axis_2.set_title(r'$\mathbf{Strong\;Scaling\;Test\;Results\;for\;a\;Large\;and\;Small\;Image}$', fontdict={'color':'#000000'})
lns = ln1+ln2+ln3
labs = [l.get_label() for l in lns]
axis_2.legend(lns, labs, loc=4)
plt.savefig("../output/graphs/strong_scaling_test_plots.png", dpi=200,bbox_inches='tight')


# fig_2 = plt.figure(2)
# plt.grid(visible=True)
# plt.plot(number_of_threads, strong_scaling_speedup_large, color='#b58900', linestyle='-', label=r'$\mathbf{Error\;Reading\; \langle E(N) \rangle = |2^{10} - \hat{I}(N)| }$')
# plt.plot(number_of_threads, strong_scaling_speedup_small, color='#b58900', linestyle='-', label=r'$\mathbf{Error\;Reading\; \langle E(N) \rangle = |2^{10} - \hat{I}(N)| }$')
# plt.plot(x_parallel, 10**log_y_parallel_best_fit, color='#b58900', linestyle='-.', label=r'$\mathbf{Best\;Fit}$', markersize=4)
# plt.xlabel('$\mathbf{N}$', fontdict={'color':'#000000'})
# plt.ylabel('$\mathbf{Absolute\;Error}$', fontdict={'color':'#000000'})
# plt.title('$\mathbf{Absolute\;Error\;vs\;N}$', fontdict={'color':'#000000'})
# plt.legend(loc=3)
# plt.savefig("./outputs/parallel_error_plot.png", dpi=300)




# strong_scaling_test_data = np.loadtxt('./generated_data/strong_scaling_test_anvil.dat')
# weak_scaling_test_data = np.loadtxt('./generated_data/weak_scaling_test_anvil.dat')

# number_of_threads = strong_scaling_test_data[0,1::3]
# strong_scaling_times = np.mean(np.transpose(strong_scaling_test_data[:,2::3]), axis=1)
# weak_scaling_times = np.mean(np.transpose(weak_scaling_test_data[:,2::3]), axis=1)

# # Calculating Speedup = T1/Tp
# strong_scaling_speedup = np.full_like(strong_scaling_times, strong_scaling_times[0])/strong_scaling_times
# weak_scaling_speedup = np.full_like(weak_scaling_times, weak_scaling_times[0])/weak_scaling_times

# fig_4, axis = plt.subplots(1,2, figsize=(10, 4))
# fig_4.tight_layout(pad=4.0)
# fig_4.subplots_adjust(wspace=0.275)
# axis[0].grid(visible=True)
# axis[0].plot(number_of_threads, strong_scaling_speedup, color='#b58900', linestyle='-', label=r'$\mathbf{Measured\;Speedup}$')
# axis[0].plot(number_of_threads, number_of_threads, color='#2aa198', linestyle='-', label=r'$\mathbf{Ideal\;Speedup}$')
# axis[0].set_xlabel('$\mathbf{Number\;of\;Processors\;(p)}$', fontdict={'color':'#000000'})
# axis[0].set_ylabel(r'$\mathbf{Speedup\;\frac{T_{1}}{T_{p}}}$', fontdict={'color':'#000000'})
# axis[0].set_title(r'$\mathbf{Strong\;Scaling\;Test\;Results}$', fontdict={'color':'#000000'})
# axis[0].legend(loc=2)

# axis[1].grid(visible=True)
# axis[1].set_ylim(0,1.4)
# axis[1].plot(number_of_threads, weak_scaling_speedup, color='#b58900', linestyle='-', label=r'$\mathbf{Measured\;Speedup}$')
# axis[1].plot(number_of_threads, np.full_like(weak_scaling_speedup,1), color='#2aa198', linestyle='-', label=r'$\mathbf{Ideal\;Speedup}$')
# axis[1].set_xlabel('$\mathbf{Number\;of\;Processors\;(p)}$', fontdict={'color':'#000000'})
# axis[1].set_ylabel(r'$\mathbf{Speedup\;\frac{T_{1}}{T_{p}}}$', fontdict={'color':'#000000'})
# axis[1].set_title(r'$\mathbf{Weak\;Scaling\;Test\;Results}$')
# axis[1].legend(loc=3)
# plt.savefig("./outputs/scaling_test_plots.png", dpi=300)
