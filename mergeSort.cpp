class Merge{
private:
	int min(int a, int b){
		if (a < b)return a;
		else return b;
	}
	int* tempArr;
public:
	//ԭ�ع鲢 ͼ1
	Merge(int arr[], int size){
		tempArr = new int[size];
	}
	void merge(int arr[], int lo, int mid, int hi){ 
		int i = lo, j = mid + 1;
		for (int k = lo; k <= hi; k++){
			tempArr[k] = arr[k];
		}

		for (int k = lo; k <= hi; k++){
			if		(i > mid)					arr[k] = tempArr[j++];
			else if (j > hi)					arr[k] = tempArr[i++];
			else if (tempArr[j] > tempArr[i])	arr[k] = tempArr[i++];
			else								arr[k] = tempArr[j++];
		}
	}
	//�Զ����¹鲢 ͼ2
	void sort(int arr[], int lo, int hi){
		if (hi <= lo) return;
		int mid = lo + (hi-lo) / 2;
		sort(arr, lo, mid);
		sort(arr, mid + 1, hi);
		merge(arr, lo, mid, hi);
	}
	//�Ե����Ϲ鲢 ͼ3
	void _sort(int arr[],int size){
		int n = size;
		if (tempArr)delete tempArr;
		tempArr = new int[size];

		for (int sz = 1; sz < n; sz += sz){
			for (int lo = 0; lo < n - sz; lo += sz + sz){
				merge(arr, lo, lo + sz - 1, min(lo + sz + sz - 1, n - 1));
			}
		}
	}

};
