import numpy as np
from matplotlib import pyplot as plt
import matplotlib.ticker as ticker
from matplotlib import rc

rc('text', usetex=True)

small_image_serial_by_factor = np.loadtxt('../time_measurements/serial_dithering_time_small.dat')
large_image_serial_by_factor = np.loadtxt('../time_measurements/serial_dithering_time_large.dat')

x_serial = small_image_serial_by_factor[:,0]

y_serial_small = small_image_serial_by_factor[:,1:]
y_serial_large = large_image_serial_by_factor[:,1:]


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



# fig_2 = plt.figure(2)
# plt.grid(visible=True)
# plt.loglog(x_parallel, y_parallel, color='#2aa198', linestyle='-', label=r'$\mathbf{Error\;Reading\; \langle E(N) \rangle = |2^{10} - \hat{I}(N)| }$')
# plt.plot(x_parallel, 10**log_y_parallel_best_fit, color='#b58900', linestyle='-.', label=r'$\mathbf{Best\;Fit}$', markersize=4)
# plt.loglog(x_parallel, expected_convergence_rate_parallel, color='#dc322f', linestyle='-', label=r'$N^{-1/2}$', markersize=4)
# plt.xlabel('$\mathbf{N}$', fontdict={'color':'#000000'})
# plt.ylabel('$\mathbf{Absolute\;Error}$', fontdict={'color':'#000000'})
# plt.title('$\mathbf{Absolute\;Error\;vs\;N}$', fontdict={'color':'#000000'})
# plt.legend(loc=3)
# plt.savefig("./outputs/parallel_error_plot.png", dpi=300)

# rosenbrock_data = np.loadtxt('./generated_data/rosenbrock_function_points.dat')
# x_rosen = rosenbrock_data[:,0]
# y_rosen = rosenbrock_data[:,1]
# z_rosen = rosenbrock_data[:,2]

# x_mesh, y_mesh = np.meshgrid(np.arange(-1.0, 1.0, 0.2), np.arange(-1.0, 1.0, 0.2))

# z_mesh = rosen([x_mesh, y_mesh])

# fig_3 = plt.figure(3)
# ax = plt.axes(projection="3d")
# generated_points = ax.scatter(x_rosen,y_rosen,z_rosen, s=3, marker="d", color="#000000", alpha=0.8)
# surf = ax.plot_surface(x_mesh, y_mesh, z_mesh, cmap=cm.hsv, linewidth=1)
# ax.set_xlabel('$\mathbf{x_{1}}$')
# ax.set_ylabel('$\mathbf{x_{2}}$')
# ax.set_zlabel('$\mathbf{Generated\;x_{3}}$')
# ax.xaxis.set_rotate_label(False)
# ax.yaxis.set_rotate_label(False)
# ax.view_init(30,60)
# fig_2.colorbar(surf, shrink=0.5, location="left")
# # plt.show()
# plt.savefig("./outputs/rosenbrock.png", dpi=300)


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

# integral_data = np.loadtxt('./generated_data/rosenbrock_integral_data.dat')
# N = integral_data[0,0::2]
# I_n = np.mean(np.transpose(integral_data[:,1::2]), axis=1)

# fig_5 = plt.figure(5)
# plt.grid(visible=True)
# plt.loglog(N, I_n, base=4, color='#2aa198', linestyle='-', label=r'$\mathbf{Integral\;Value}$')
# plt.xlabel('$\mathbf{Number\;of\;Points\;(N)}$', fontdict={'color':'#000000'})
# plt.ylabel(r'$\mathbf{Calculated\;Integral\;Value\;\;\hat{I}(N)}$', fontdict={'color':'#000000'})
# plt.title(r'$\mathbf{Number\;of\;Threads\;vs\;Speedup\;\frac{T_{1}}{T_{P}}}$', fontdict={'color':'#000000'})
# plt.legend(loc=4)
# plt.savefig("./outputs/integral_vs_N.png", dpi=300)

# serial_error_estimator_data = np.loadtxt('./generated_data/serial_error_estimator.dat')
# parallel_error_estimator_data = np.loadtxt('./generated_data/parallel_error_estimator.dat')

# N = serial_error_estimator_data[0,0::3]

# serial_integral_values = serial_error_estimator_data[:,1::3]
# parallel_integral_values = parallel_error_estimator_data[:,1::3]

# serial_estimated_errors = np.mean(np.transpose(serial_error_estimator_data[:,2::3]), axis=1)
# parallel_estimated_errors = np.mean(np.transpose(parallel_error_estimator_data[:,2::3]), axis=1)

# serial_actual_errors = np.mean(np.transpose(np.absolute(1024 - serial_integral_values)), axis=1)
# parallel_actual_errors = np.mean(np.transpose(np.absolute(1024 - parallel_integral_values)), axis=1)

# log_N = np.emath.logn(4, N)

# serial_log_E = np.emath.logn(4, serial_estimated_errors)
# parallel_log_E = np.emath.logn(4, parallel_estimated_errors)

# A_serial,B_serial = np.polyfit(log_N, serial_log_E, 1)
# A_parallel,B_parallel = np.polyfit(log_N, parallel_log_E, 1)

# print("Rate of descent of the Series error estimator is = ", A_serial)
# print("Rate of descent of the Parallel error estimator is = ", A_parallel)

# serial_log_E_best_fit = A_serial*log_N + B_serial
# parallel_log_E_best_fit = A_parallel*log_N + B_parallel

# fig_6, axis_1 = plt.subplots(1,2, figsize=(10, 4))
# fig_6.tight_layout(pad=4.0)
# fig_6.subplots_adjust(wspace=0.275)
# axis_1[0].grid(visible=True)
# axis_1[0].loglog(N, serial_estimated_errors, base=4, color='#2aa198', linestyle='-', linewidth=2, label=r'$\mathbf{Estimated\;Error}$')
# axis_1[0].loglog(N, serial_actual_errors, base=4, color='#b58900', linestyle='-', linewidth=2, label=r'$\mathbf{Actual\;Error}$')
# axis_1[0].plot(N, 4**serial_log_E_best_fit, color='#dc322f', linestyle='--', linewidth=2, label=r'$\mathbf{Best\;Fit}$', markersize=4)
# axis_1[0].set_xlabel('$\mathbf{N}$', fontdict={'color':'#000000'})
# axis_1[0].set_ylabel('$\mathbf{Absolute\;Error}$', fontdict={'color':'#000000'})
# axis_1[0].set_title('$\mathbf{Error\;Estimator\;(Serial\;Code)}$', fontdict={'color':'#000000'})
# axis_1[0].legend(loc=3)

# axis_1[1].grid(visible=True)
# axis_1[1].loglog(N, parallel_estimated_errors, base=4, color='#2aa198', linestyle='-', linewidth=2, label=r'$\mathbf{Estimated\;Error}$')
# axis_1[1].loglog(N, parallel_actual_errors, base=4, color='#b58900', linestyle='-', linewidth=2, label=r'$\mathbf{Actual\;Error}$')
# axis_1[1].plot(N, 4**parallel_log_E_best_fit, color='#dc322f', linestyle='--', linewidth=2, label=r'$\mathbf{Best\;Fit}$', markersize=4)
# axis_1[1].set_xlabel('$\mathbf{N}$', fontdict={'color':'#000000'})
# axis_1[1].set_ylabel('$\mathbf{Absolute\;Error}$', fontdict={'color':'#000000'})
# axis_1[1].set_title('$\mathbf{Error\;Estimator\;(Parallel\;Code)}$', fontdict={'color':'#000000'})
# axis_1[1].legend(loc=3)
# plt.savefig("./outputs/error_estimator_plots.png", dpi=300)
