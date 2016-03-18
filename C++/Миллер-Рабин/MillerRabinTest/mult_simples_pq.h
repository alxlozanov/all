
// ������� �2 - ��������� ������������ ���� ������� ����� �� ��������� ������� simples.
// ��������, ������ �������� ��� ������� ����� �� 3 �� 1��� - �� ������� ������������ ������������ ���������� ����� leftBorder � rightBorder(�.�. � ������) - 
// � ������� ��������� �������� ������ �������-������ ����� � ����. ���� ��� ���������, � �������� ��������!
void thread_function_mult_simples(uint64_t  leftBorder, uint64_t  rightBorder, uint64_t  maxCount, uint64_t  * simples, mutex*locker, FILE *fout, vector<uint128_t> *spps)
{
	uint64_t  multResult = 0;
	uint64_t  j = 0;
	int count = 3;

	uint128_t * print_values = new uint128_t[ count ];

	for (uint64_t  i = leftBorder; i < rightBorder && i < maxCount; i++) {
		
		for (j = leftBorder; j < maxCount; j++) {
			multResult = simples[i] * simples[j];// ������ ��������� �����

			if (LABS_TEST_MILLER_RABIN_uint64_t( &multResult, A_LENGTH ) ) {

				// ���� ��������� ����� ������ �������� - ��� ��������� � ����
				locker->lock();

				if (std::find(spps->begin(), spps->end(), multResult) == spps->end()) {

					print_values[0] = multResult;
					print_values[1] = simples[i];
					print_values[2] = simples[j];

					spps->push_back(multResult);

					printValues(print_values, &count , fout);
				}

				locker->unlock();
			}
		}
	}

	delete[] print_values;
}

// �������, ������� ��������� ��� ������� ����� � ���������� �� start �� finish � ������� ������� thread_function_mult_simples 
void mult_simples_pq_run() {

	// ������������ ���������� ������� �����. �� ��������� ����� ������� ������� ���������������� ����������
	uint64_t  max_count_simples = 1000000;
	uint64_t  *simples = new uint64_t[max_count_simples];

	// ������� ���������� ������� ����� � ��� ������� �����
	uint64_t  count_simples = 0;// getCountSimples(3, max_count_simples, simples);
	getPrimes(simples, &count_simples, 0, max_count_simples, 1);

	uint64_t  step = count_simples / 30;

	std::atomic<bool> * is_completed_threads = NULL;
	FILE *f = NULL;

	ThreadsManager 	example;
	fprintf(example.FOUT_FILE, "����������: �� %lld, ������� ����� ����� : %lld, ������������ ����� = %lld\n\n", max_count_simples, count_simples, simples[count_simples - 2]);
	printf("����������: �� %lld, ������� ����� ����� : %lld, ������������ ����� = %lld\n\n", max_count_simples, count_simples, simples[count_simples - 2]);


	example.parallel_by_cores(is_completed_threads, f, count_simples, simples, step, 2000, thread_function_mult_simples);
}

