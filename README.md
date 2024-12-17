# ИДЗ-4 АВС

Закревский Назар, БПИ-236

--- 

### Вариант 6
__Условие задания__

Базу данных разделяют два типа потоков читатели и писатели. Читатели периодически просматривают случайные записи базы данных и выводя номер свой номер, индекс записи и ее значение. Писатели изменяют случайные записи на случайное число и также выводят информацию о своем номере, индексе записи, старом значении и новом значении. Предполагается, что в начале БД находится в непротиворечивом состоянии (все числа отсортированы). Каждая отдельная новая запись переводит БД из одного непротиворечиво-го состояния в другое (то есть, новая сортировка может поменять индексы записей). Транзакции выполняются в режиме «грязного чтения». То есть, процесс-писатель не может получить доступ к БД только в том случае, если ее уже занял другой процесс-писатель, а процессы-читатели ему не мешают обратиться к БД. Поэтому он может изменять базу данных, когда в неи находятся читате-ли. Создать многопоточное приложение с потоками-писателями и потоками-читателями.

---

Для начала опишем сущности, которые будут участвовать в нашей задаче:
- Читатели
- Писатели

Реализация всего процесса лежит в папке rw-lock, в ней приведены оба решения, а также примеры работы программы.
В папке rw-lock/condition_variable лежит решение с использованием условных переменных, а в папке rw-lock/semaphore - решение с использованием семафоров.
В папке rw-lock/report_images приложены все фотографии как результат работы программы.

Организован запрос ввода с повторным запросом в случае некорректного ввода. Ввод данных происходит во время выполнения программы.

### Структура проекта
```sh
└── IDZ-4_Assembly_/
    ├── CMakeLists.txt
    ├── README.md
    ├── ReadData
    │   └── load_data.cpp
    ├── RwLockImpl
    │   ├── report_images
    │   ├── rw-lock_OpenMP.cpp
    │   ├── rw-lock_condvar.cpp
    │   └── rw-lock_mutex.cpp
    ├── cmake-build-debug
    │   ├── .cmake
    │   ├── .ninja_deps
    │   ├── .ninja_log
    │   ├── CMakeCache.txt
    │   ├── CMakeFiles
    │   ├── IDZ_4_Assembly
    │   ├── Testing
    │   ├── asff
    │   ├── build.ninja
    │   ├── cmake_install.cmake
    │   └── output
    ├── input.txt
    └── main.cpp
```


###  Project Index
<details open>
	<summary><b><code>IDZ-4_ASSEMBLY_/</code></b></summary>
	<details> <!-- __root__ Submodule -->
		<summary><b>__root__</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/CMakeLists.txt'>CMakeLists.txt</a></b></td>
				<td><code>❯ Конфигурационный файл</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/input.txt'>input.txt</a></b></td>
				<td><code>❯ Файл для вввода данных</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/main.cpp'>main.cpp</a></b></td>
				<td><code>❯ Основной метод</code></td>
			</tr>
			</table>
		</blockquote>
	</details>
	<details> <!-- ReadData Submodule -->
		<summary><b>ReadData</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/ReadData/load_data.cpp'>load_data.cpp</a></b></td>
				<td><code>❯ Метод для считывания данных из файла или консоли </code></td>
			</tr>
			</table>
		</blockquote>
	</details>
	<details> <!-- RwLockImpl Submodule -->
		<summary><b>RwLockImpl</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/RwLockImpl/rw-lock_mutex.cpp'>rw-lock_mutex.cpp</a></b></td>
				<td><code>❯ Реализация rw-lock с помощью 2 mutex-ов</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/RwLockImpl/rw-lock_OpenMP.cpp'>rw-lock_OpenMP.cpp</a></b></td>
				<td><code>❯ Реализация rw-lock с помощью condition_variable</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/RwLockImpl/rw-lock_condvar.cpp'>rw-lock_condvar.cpp</a></b></td>
				<td><code>❯ Реализация rw-lock с помощью OpenMP</code></td>
			</tr>
			</table>
		</blockquote>
	</details>
	<details> <!-- cmake-build-debug Submodule -->
		<summary><b>cmake-build-debug</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/cmake_install.cmake'>cmake_install.cmake</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.ninja_log'>.ninja_log</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.ninja_deps'>.ninja_deps</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/IDZ_4_Assembly'>IDZ_4_Assembly</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/output'>output</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/build.ninja'>build.ninja</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeCache.txt'>CMakeCache.txt</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/asff'>asff</a></b></td>
				<td><code>❯ REPLACE-ME</code></td>
			</tr>
			</table>
			<details>
				<summary><b>CMakeFiles</b></summary>
				<blockquote>
					<table>
					<tr>
						<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/clion-environment.txt'>clion-environment.txt</a></b></td>
						<td><code>❯ REPLACE-ME</code></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/TargetDirectories.txt'>TargetDirectories.txt</a></b></td>
						<td><code>❯ REPLACE-ME</code></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/clion-Debug-log.txt'>clion-Debug-log.txt</a></b></td>
						<td><code>❯ REPLACE-ME</code></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/CMakeConfigureLog.yaml'>CMakeConfigureLog.yaml</a></b></td>
						<td><code>❯ REPLACE-ME</code></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/cmake.check_cache'>cmake.check_cache</a></b></td>
						<td><code>❯ REPLACE-ME</code></td>
					</tr>
					<tr>
						<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/rules.ninja'>rules.ninja</a></b></td>
						<td><code>❯ REPLACE-ME</code></td>
					</tr>
					</table>
					<details>
						<summary><b>3.27.8</b></summary>
						<blockquote>
							<table>
							<tr>
								<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CMakeCXXCompiler.cmake'>CMakeCXXCompiler.cmake</a></b></td>
								<td><code>❯ REPLACE-ME</code></td>
							</tr>
							<tr>
								<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CMakeDetermineCompilerABI_C.bin'>CMakeDetermineCompilerABI_C.bin</a></b></td>
								<td><code>❯ REPLACE-ME</code></td>
							</tr>
							<tr>
								<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CMakeDetermineCompilerABI_CXX.bin'>CMakeDetermineCompilerABI_CXX.bin</a></b></td>
								<td><code>❯ REPLACE-ME</code></td>
							</tr>
							<tr>
								<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CMakeCCompiler.cmake'>CMakeCCompiler.cmake</a></b></td>
								<td><code>❯ REPLACE-ME</code></td>
							</tr>
							<tr>
								<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CMakeSystem.cmake'>CMakeSystem.cmake</a></b></td>
								<td><code>❯ REPLACE-ME</code></td>
							</tr>
							</table>
							<details>
								<summary><b>CompilerIdC</b></summary>
								<blockquote>
									<table>
									<tr>
										<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CompilerIdC/CMakeCCompilerId.c'>CMakeCCompilerId.c</a></b></td>
										<td><code>❯ REPLACE-ME</code></td>
									</tr>
									</table>
								</blockquote>
							</details>
							<details>
								<summary><b>CompilerIdCXX</b></summary>
								<blockquote>
									<table>
									<tr>
										<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/CMakeFiles/3.27.8/CompilerIdCXX/CMakeCXXCompilerId.cpp'>CMakeCXXCompilerId.cpp</a></b></td>
										<td><code>❯ REPLACE-ME</code></td>
									</tr>
									</table>
								</blockquote>
							</details>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<details>
				<summary><b>.cmake</b></summary>
				<blockquote>
					<details>
						<summary><b>api</b></summary>
						<blockquote>
							<details>
								<summary><b>v1</b></summary>
								<blockquote>
									<details>
										<summary><b>query</b></summary>
										<blockquote>
											<table>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/query/codemodel-v2'>codemodel-v2</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/query/cmakeFiles-v1'>cmakeFiles-v1</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/query/toolchains-v1'>toolchains-v1</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/query/cache-v2'>cache-v2</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											</table>
										</blockquote>
									</details>
									<details>
										<summary><b>reply</b></summary>
										<blockquote>
											<table>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/toolchains-v1-a6738bc6e8a56d97ac62.json'>toolchains-v1-a6738bc6e8a56d97ac62.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/target-IDZ_4_Assembly-Debug-20abe68c4929bdadba4f.json'>target-IDZ_4_Assembly-Debug-20abe68c4929bdadba4f.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/directory-.-Debug-f5ebdc15457944623624.json'>directory-.-Debug-f5ebdc15457944623624.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/codemodel-v2-3c903fad393da23b99f4.json'>codemodel-v2-3c903fad393da23b99f4.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/cache-v2-003e91d81b769a8ab5a6.json'>cache-v2-003e91d81b769a8ab5a6.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/index-2024-12-06T07-37-11-0195.json'>index-2024-12-06T07-37-11-0195.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											<tr>
												<td><b><a href='https://github.com/naziikk/IDZ-4_Assembly_/blob/master/cmake-build-debug/.cmake/api/v1/reply/cmakeFiles-v1-1cc5d2ba7447da9d5a60.json'>cmakeFiles-v1-1cc5d2ba7447da9d5a60.json</a></b></td>
												<td><code>❯ REPLACE-ME</code></td>
											</tr>
											</table>
										</blockquote>
									</details>
								</blockquote>
							</details>
						</blockquote>
					</details>
				</blockquote>
			</details>
		</blockquote>
	</details>
</details>

---


### Базовые требования на 8 баллов
 - В отчете должен быть приведен сценарий, описывающий одновременное поведение представленных в условии задания сущностей в
терминах предметной области. То есть, описан сценарий, задающий ролевое поведение субъектов и объектов задачи (интерпретация условия с большей степенью детализации происходящего), а не
то, как это будет реализовано в программе. ✅

```
    Вся задача сводится к базовой задаче rw-lock (readers-writers lock)
    https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock

    Для первого решения опишем алгоритм:
    
    Мы имеем 2 mutex-а: один отвечает за писателей, второй — за читателей.
    Также фиксируем счетчик читателей, которые в данный момент просматривают базу данных.
    При появлении нового читателя блокируем поток читателей, инкрементируем счетчик и, если счетчик становится равен 1, блокируем писателей.
    После завершения чтения декрементируем счетчик. Если он становится равен 0, разблокируем писателей.
    Далее рассмотрим решение 2, используя condition_variable.
    
    Для этого опишем алгоритм:
    
    Мы имеем 2 condition_variable: один отвечает за писателей, второй — за читателей.
    Для чтения:
    Читатель захватывает mutex и ожидает, пока не станет доступным чтение (нет активного писателя).
    После проверки условий увеличиваем счетчик активных читателей и освобождаем mutex.
    После завершения чтения уменьшаем счетчик активных читателей. Если он становится равен 0, уведомляем поток писателей.
    Для записи:
    Писатель захватывает mutex и ожидает, пока не станет доступным запись (нет активных читателей и писателя).
    После проверки условий помечаем, что писатель активен, и освобождаем mutex.
    После завершения записи освобождаем флаг активности писателя и уведомляем как читателей, так и других писателей.
```

 - Описана модель параллельных вычислений, используемая при разработке многопоточной программы.✅
 - Описаны входные данные программы, включающие вариативные
диапазоны, возможные при многократных запусках. ✅
 - Реализовано консольное приложение, решающее поставленную задачу с использованием одного варианта изученных синхропримитивов.✅
 - Ввод данных в приложение реализован с консоли во время выполнения программы (без использования аргументов командной строки).✅
 - Для используемых генераторов случайных чисел описаны их диапазоны и то, как интерпретируются данные этих генераторов.✅
 - Вывод программы должен быть информативным, отражая все ключевые протекающие в ней события в терминах предметной области.
   Наблюдатель на основе вывода программы должен понимать, что
   в ней происходит в каждый момент времени ее работы.
   
*Пример моего вывода:*

```
Writer changing the 3 note...
New note - fDssqEQ
----------------------------------------------------------------------------
Reader reading the 1 note...
Read note: FoUAI9URfJ5U
----------------------------------------------------------------------------
Reader reading the 2 note...
Read note: tnytbvstny
----------------------------------------------------------------------------
Reader reading the 3 note...
Read note: fDssqEQ
----------------------------------------------------------------------------
Reader reading the 3 note...
Read note: fDssqEQ
----------------------------------------------------------------------------
Reader reading the 3 note...
Read note: fDssqEQ
----------------------------------------------------------------------------
Writer changing the 1 note...
New note - s55f6xX1rv2q
----------------------------------------------------------------------------
Reader reading the 0 note...
Read note: rbnbrerbtnfyhm
----------------------------------------------------------------------------
Reader reading the 0 note...
Read note: rbnbrerbtnfyhm
----------------------------------------------------------------------------
New data:
rbnbrerbtnfyhm
s55f6xX1rv2q
tnytbvstny
fDssqEQ
```
 - В программе присутствуют комментарии, поясняющие выполняемые действия и описание используемых объектов и переменных.✅
 - Результаты работы программы представлены в отчете.✅
 - В программу, наряду с выводом в консоль, добавлен вывод результатов в файл. Имя файла для вывода данных задается в командной
   строке как один из ее параметров.✅
 - Результаты работы программы должны выводиться на экран и записываться в файл.✅
 - Наряду с вводом исходных данных через командную строку добавлен альтернативный вариант их ввода из файла, который по сути
   играет роль конфигурационного файла. Имя этого файла задается
   в командной строке вместо параметров, которые в этом случае не
   вводятся. Управление вводом в командной строке осуществляется
   с использованием соответствующих ключей.✅

### 9 баллов 
- Помимо программы на оценку в 8 баллов разработать еще одну программу удовлетворяющую следующим условиям:
Разработано альтернативное решение, построенное на других синхропримитивах. При этом следует учесть, что мьютексы и семафоры — это по сути один тип синхропримитивов. Поэтому мьютексы
на семафоры и обратно не обменивать. При их наличии в первой
программе следует использовать что-то еще. Но допускается использовать мьютексы (как простейшие синхропримитивы) наряду
с другими новыми синхропримитивами.✅

Выше был описан алгоритм решения использующий условные переменные и мьютексы. 

 - Приведен сравнительный анализ поведения с ранее разработанной
программой. Он заключается в проверке идентичности поведения
при одинаковых данных. ✅

*Все работает действительно идентично, вывод данных в консоль демонстрирует это*


### 10 баллов

Разработано решение используя OpenMp и находится в файле RwLockImpl/rw-lock_OpenMP.cpp

 - Проведен сравнительный анализ поведения с ранее разработанными программами. Он заключается в проверке идентичности поведения при одинаковых данных.✅
   Все работает абсолютно идентично, вывод данных в консоль демонстрирует это.
   Чтобы собрать файл с OpenMP необходимо установить библиотеку, а затем собрать файл с флагом -fopenmp
   
   Мое решение разрабатывалось на MacOS, поэтому для сборки программы необходимо использовать следующую команду:
   ```
    g++ -fopenmp rw-lock_OpenMP.cpp -o rw-lock_OpenMP
    ```
    До этого с помощью HomeBrew необходимо установить OpenMP и gcc:
   ```
   brew install llvm
   brew install libomp
   breq install gcc
   ```
   
---


